import os
import sys
import subprocess
import platform
import shutil
import zipfile

import urllib.request


class BoostGetter:
    def __init__(self, boost_version, extract_base_path=None):
        if not isinstance(boost_version, str):
            raise ValueError("Boost version must be a string.")

        if len(boost_version.split(".")) < 3:
            boost_version += ".0"

        self.boost_version = boost_version
        self.boost_version_ = boost_version.replace(".", "_")
        self.archive_name = f"boost_{self.boost_version_}.zip"
        self.download_url = f"https://archives.boost.io/release/{self.boost_version}/source/{self.archive_name}"

        if extract_base_path is not None:
            self.extract_base_path = extract_base_path
        else:
            self.extract_base_path = os.getcwd()

        self.extract_dir = os.path.join(self.extract_base_path, f"boost_{self.boost_version_}")

    def list_versions(self, max=10):
        print("Available Boost versions (https://archives.boost.io/release/):")
        url = "https://archives.boost.io/release/"
        response = urllib.request.urlopen(url)
        html = response.read().decode("utf-8")
        versions = []
        for line in html.splitlines():
            if "href" in line:
                link_name = line.split('href="')[1].split('"')[0]
                link_name_numbers = link_name.split(".")
                if len(link_name_numbers) != 3:
                    continue

                version = link_name.replace("/", "")

                try:
                    version_int = tuple(map(int, version.split(".")))
                except Exception as e:
                    continue

                versions.append(version)

        versions = sorted(versions, key=lambda x: tuple(map(int, x.split("."))), reverse=True)

        if len(versions) <= max:
            for version in versions:
                print(f"'{version}'")
        else:
            versions = versions[:max]
            for version in versions:
                print(f"'{version}'")
            print("...")

    def download(self, clean=False):
        self.current_dir = os.getcwd()
        os.chdir(self.extract_base_path)

        if os.path.exists(self.extract_dir):
            if clean:
                self.clean()
            else:
                print(f"Boost source directory '{self.extract_dir}' already exists.")
                print(f"set parameter clean=True to overwrite it.")
                return

        print(f"Downloading {self.download_url}...")
        urllib.request.urlretrieve(self.download_url, self.archive_name)
        print(f"Extracting {self.archive_name}...")
        with zipfile.ZipFile(self.archive_name, "r") as archive:
            archive.extractall()
        print(f"Extracted to {os.path.join(os.getcwd(), self.archive_name)}")
        print(f"Removing {self.archive_name}...")
        os.remove(self.archive_name)
        if not os.path.exists(self.extract_dir):
            raise FileNotFoundError(f"Failed to extract Boost source directory '{self.extract_dir}'.")
        os.chdir(self.current_dir)

    def clean(self):
        if not self.extract_dir:
            raise ValueError("Boost version not set. Please call download() first.")

        if os.path.exists(self.extract_dir):
            print(f"Removing {self.extract_dir}...")
            shutil.rmtree(self.extract_dir)
        else:
            print(f"Boost source directory '{self.extract_dir}' does not exist.")

    def configure(self, toolset=None, clean=False):
        if not self.extract_dir:
            raise ValueError("Boost version not set. Please call download() first.")

        self.toolset = toolset
        self.extract_dir = f"boost_{self.boost_version_}"

        if not os.path.exists(self.extract_dir):
            raise FileNotFoundError(
                f"Boost source directory '{self.extract_dir}' does not exist. Please call download() first."
            )

        # save current directory
        self.current_dir = os.getcwd()
        os.chdir(self.extract_dir)
        
        
        if platform.system().lower().startswith("win"):
            self.b2_cmd = ["b2.exe"]
        else:
            self.b2_cmd = ["./b2"]
        if os.path.exists("b2") and not clean:
            print(f"b2 already exists in {os.getcwd()}, set clean=True to overwrite it.")
            return
        
        if platform.system().lower().startswith("win"):
            
            bootstrap_command = ["bootstrap.bat"]
            if self.toolset:
                bootstrap_command += [f"{self.toolset}"]

            subprocess.check_call(["cmd", "/c", *bootstrap_command])
        else:            
            subprocess.check_call(["chmod", "+x", "bootstrap.sh"])
            subprocess.check_call(["chmod", "+x", "tools/build/src/engine/build.sh"])

            print(f"Running bootstrap.sh... in {os.getcwd()}")
            bootstrap_command = ["./bootstrap.sh"]
            if self.toolset:
                bootstrap_command += [f"--with-toolset={self.toolset}"]
                
            print(f"Running command: {bootstrap_command}")

            subprocess.check_call([*bootstrap_command])
        os.chdir(self.current_dir)

    def install(self, boost_modules, toolset=None):
        
        if toolset is None:
            toolset = self.get_default_toolset()
            
        self.boost_modules = [f'--with-{module}' for module in boost_modules]
        self.current_dir = os.getcwd()
        os.chdir(self.extract_dir)
        self.b2_cmd += ["--variant=release", "--threading=multi", "--link=static"] + self.boost_modules
        subprocess.check_call(self.b2_cmd)
        os.chdir(self.current_dir)

    def get_default_toolset(self):
        if platform.system().lower().startswith("win"):
            # Windows
            if os.path.exists("C:\\Program Files (x86)\\Microsoft Visual Studio"):
                return "vc143"
            elif os.path.exists("C:\\Program Files\\Microsoft Visual Studio"):
                return "vc143"
            else:
                raise EnvironmentError("No compatible Visual Studio installation found.")
        elif platform.system().lower() == "linux":
            # Linux
            return "g++"
        else:
            # macOS
            return "clang"

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if os.path.exists(self.current_dir):
            os.chdir(self.current_dir)
        if exc_type is not None:
            print(f"An error occurred: {exc_value}")
            return False
        return True


def main(boost_version, toolset, boost_modules):
    booster = BoostGetter(boost_version, toolset, boost_modules)
    booster.download()
    booster.configure()
    booster.install()


if __name__ == "__main__":
    # Example usage: python get_boost.py 1.78.0 msvc "context filesystem"
    boost_version = sys.argv[1]
    toolset = sys.argv[2]
    boost_modules = sys.argv[3:]
    main(boost_version, toolset, boost_modules)
