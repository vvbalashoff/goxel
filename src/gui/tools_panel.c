/* Goxel 3D voxels editor
 *
 * copyright (c) 2019 Guillaume Chereau <guillaume@noctua-software.com>
 *
 * Goxel is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.

 * Goxel is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * goxel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "goxel.h"

#ifndef GUI_TOOLS_COLUMNS_NB
#   define GUI_TOOLS_COLUMNS_NB 4
#endif


// XXX: better replace this by something more automatic.
static void auto_grid(int nb, int i, int col)
{
    if ((i + 1) % col != 0) gui_same_line();
}

void gui_tools_panel(void)
{
    const struct {
        int         tool;
        const char  *tool_id;
        int         icon;
    } values[] = {
        {TOOL_BRUSH,        "brush",        ICON_TOOL_BRUSH},
        {TOOL_SHAPE,        "shape",        ICON_TOOL_SHAPE},
        {TOOL_LASER,        "laser",        ICON_TOOL_LASER},
        {TOOL_SET_PLANE,    "plane",        ICON_TOOL_PLANE},
        {TOOL_MOVE,         "move",         ICON_TOOL_MOVE},
        {TOOL_PICK_COLOR,   "pick_color",   ICON_TOOL_PICK},
        {TOOL_SELECTION,    "selection",    ICON_TOOL_SELECTION},
        {TOOL_FUZZY_SELECT, "fuzzy_select", ICON_TOOL_FUZZY_SELECT},
        {TOOL_EXTRUDE,      "extrude",      ICON_TOOL_EXTRUDE},
        {TOOL_LINE,         "line",         ICON_TOOL_LINE},
        {TOOL_PROCEDURAL,   "procedural",   ICON_TOOL_PROCEDURAL},
    };
    const int nb = ARRAY_SIZE(values);
    int i;
    bool v;
    char action_id[64];
    char label[64];
    const action_t *action = NULL;
    const tool_t *tool;

    gui_group_begin(NULL);
    for (i = 0; i < nb; i++) {
        tool = tool_get(values[i].tool);
        v = goxel.tool->id == values[i].tool;
        sprintf(label, "%s", tool->name);
        if (values[i].tool_id) {
            sprintf(action_id, "tool_set_%s", values[i].tool_id);
            action = action_get(action_id, true);
            assert(action);
            if (*action->shortcut)
                sprintf(label, "%s (%s)", tool->name, action->shortcut);
        }
        if (gui_selectable_icon(label, &v, values[i].icon)) {
            action_exec(action, "");
        }
        auto_grid(nb, i, GUI_TOOLS_COLUMNS_NB);
    }
    gui_group_end();

    if (gui_collapsing_header(goxel.tool->name, true))
        tool_gui(goxel.tool);
}
