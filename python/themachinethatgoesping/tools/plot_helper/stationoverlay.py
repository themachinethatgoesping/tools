from typing import Any, Dict, Optional, Tuple

import matplotlib.pyplot as plt

# Qt-style names -> matplotlib linestyles (native ones pass through)
_STYLE_MAP = {
    'solid': '-',
    'dash': '--',
    'dot': ':',
    'dashdot': '-.',
}


class StationOverlay:
    """Draws and manages station time markers on a single matplotlib Axes."""

    def __init__(self, ax: plt.Axes):
        self.ax = ax
        # station_name -> {'lines': [...], 'regions': [...], 'labels': [...]}
        self._artists: Dict[str, Dict[str, list]] = {}

    def add_station_times(
        self,
        stations: Dict[str, Tuple[Any, Any]],
        line_color: str = '#424242',
        line_width: float = 2,
        line_style: str = 'dash',
        region_color: Optional[str] = None,
        region_alpha: float = 0.15,
        label_color: Optional[str] = None,
        label_size: Any = 10,
        label_position: str = 'top',
        label_rotation: float = 0,
        zorder: float = 10,
    ) -> None:
        """Add station time markers (lines + optional region + label) to `self.ax`.

        Parameters
        ----------
        stations : dict mapping station name -> (start_time, end_time)
        line_color, line_width, line_style : style of the start/end vertical lines.
            line_style accepts Qt names ('solid', 'dash', 'dot', 'dashdot')
            or matplotlib names ('-', '--', ':', '-.').
        region_color, region_alpha : optional shaded axvspan between the lines.
        label_color : defaults to line_color if None.
        label_size : float (points) or a string like '10pt'.
        label_position : 'top' or 'bottom' (axes-fraction height of the label).
        label_rotation : rotation of the label text in degrees.
        zorder : drawn above typical data (images are ~zorder 0, lines ~2).
        """
        pen_style = _STYLE_MAP.get(line_style, line_style)
        effective_label_color = label_color if label_color is not None else line_color

        # '10pt' -> 10
        if isinstance(label_size, str) and label_size.endswith('pt'):
            try:
                label_size = float(label_size[:-2])
            except ValueError:
                pass

        y_frac = 1.0 if label_position == 'top' else 0.0
        va = 'top' if label_position == 'top' else 'bottom'
        # small padding inward from the axes edge
        y_pad = -0.01 if label_position == 'top' else 0.01

        for station_name, (start_time, end_time) in stations.items():
            entry = self._artists.setdefault(
                station_name, {'lines': [], 'regions': [], 'labels': []})

            if region_color is not None:
                entry['regions'].append(self.ax.axvspan(
                    start_time, end_time,
                    facecolor=region_color, alpha=region_alpha,
                    lw=0, zorder=zorder - 0.5))

            for t in (start_time, end_time):
                entry['lines'].append(self.ax.axvline(
                    t,
                    color=line_color, linewidth=line_width,
                    linestyle=pen_style, zorder=zorder))

            x_mid = start_time + (end_time - start_time) / 2
            entry['labels'].append(self.ax.text(
                x_mid, y_frac + y_pad, station_name,
                transform=self.ax.get_xaxis_transform(),  # x=data, y=axes fraction
                color=effective_label_color, fontsize=label_size,
                ha='center', va=va, rotation=label_rotation,
                zorder=zorder + 1))

        self.ax.figure.canvas.draw_idle()

    def clear_station_times(self, station_name: Optional[str] = None) -> None:
        """Remove one station's artists, or all stations if name is None."""
        if station_name is not None:
            entry = self._artists.pop(station_name, None)
            if entry is not None:
                for group in entry.values():
                    for artist in group:
                        artist.remove()
        else:
            for entry in self._artists.values():
                for group in entry.values():
                    for artist in group:
                        artist.remove()
            self._artists.clear()
        self.ax.figure.canvas.draw_idle()

    def get_station_names(self):
        """Names currently overlaid (useful for mirroring _station_data_list)."""
        return list(self._artists.keys())


def add_station_times(
    ax: plt.Axes,
    stations: Dict[str, Tuple[Any, Any]],
    **kwargs,
) -> StationOverlay:
    """One-shot convenience wrapper: creates an overlay, adds stations, returns it
    (keep the returned object if you ever want to clear/remove markers)."""
    overlay = StationOverlay(ax)
    overlay.add_station_times(stations, **kwargs)
    return overlay