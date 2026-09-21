
def compare(object1, object2):
    """
    Compare string representations of two objects and display the differences as HTML in a Jupyter notebook.

    Args:
        object1: The first object to compare.
        object2: The second object to compare.
    """
    try:
        from diff_match_patch import diff_match_patch
    except ImportError as e:
        raise ImportError("compare: The diff_match_patch module is required for this functionality. "
                          "Please install it using 'pip install diff-match-patch'.") from e


    dmp = diff_match_patch()
    diffs = dmp.diff_main(
        str(object1),
        str(object2), 
    )
    dmp.diff_cleanupSemantic(diffs)

    html = ''
    for op, text in diffs:
        if op == 0:
            html += f'<span>{text}</span>'
        elif op == 1:
            html += f'<span style="background:#e6ffcc">{text}</span>'   # added
        else:
            html += f'<span style="background:#ffe6e6;text-decoration:line-through">{text}</span>'

    from IPython.display import HTML, display
    display(HTML(f'<pre>{html}</pre>'))