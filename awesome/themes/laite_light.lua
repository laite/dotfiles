-------------------------------
--  "laite2" awesome theme  --
--    By Adrian C. (anrxc)   --
-------------------------------

-- Alternative icon sets and widget icons:
--  * http://awesome.naquadah.org/wiki/Nice_Icons

-- {{{ Main
theme = {}
theme.wallpaper_cmd = { "feh --bg-center /home/laite/.config/awesome/wall.png" }
-- }}}

-- {{{ Styles
theme.font      = "Sans 8"

-- {{{ Colors
theme.fg_normal = "#1a1a1a"
theme.fg_focus  = "#ffffff"
theme.fg_urgent = "#ffffff"
theme.fg_additi = "#ff8833"
theme.bg_normal = "#ffffff"
theme.bg_focus  = "#8aab68"
theme.bg_urgent = "#8aab68"
-- }}}

-- {{{ Borders
theme.border_width  = "1"
theme.border_normal = "#d6d6d6"
theme.border_focus  = "#1a1a1a"
theme.border_terminal = "#101010" -- background of URxvt (as 2012/12/18 anyway :P)
theme.border_terminal_focus = "#8aab68"
theme.border_marked = "#CCAC8C"
-- }}}

-- {{{ Titlebars
theme.titlebar_bg_focus  = "#3F3F3F"
theme.titlebar_bg_normal = "#3F3F3F"
-- }}}

-- {{{ Mouse finder
theme.mouse_finder_color = "#CC9393"
-- mouse_finder_[timeout|animate_timeout|radius|factor]
-- }}}

-- {{{ Menu
-- Variables set for theming the menu:
-- menu_[bg|fg]_[normal|focus]
-- menu_[border_color|border_width]
theme.menu_height = "15"
theme.menu_width  = "100"
-- }}}

-- {{{ Icons
-- {{{ Taglist
theme.taglist_squares_sel   = "/home/laite/.config/awesome/themes/zenburn/taglist/squarefz.png"
theme.taglist_squares_unsel = "/home/laite/.config/awesome/themes/zenburn/taglist/squarez.png"
--theme.taglist_squares_resize = "false"
-- }}}

-- {{{ Misc
theme.awesome_icon           = "/home/laite/.config/awesome/themes/zenburn/awesome-icon.png"
theme.menu_submenu_icon      = "/home/laite/.config/awesome/themes/default/submenu.png"
theme.tasklist_floating_icon = "/home/laite/.config/awesome/themes/zenburn/tasklist/floating.png"
-- }}}

-- {{{ Layout indicators
-- text version
theme.layout_txt_tile       = " ⁝ tiled" 
theme.layout_txt_tileleft   = " ⁝ tiled left"
theme.layout_txt_tilebottom = " ⁝ tiled bottom"
theme.layout_txt_tiletop    = " ⁝ tiled top"
theme.layout_txt_fairv      = " ⁝ fair vertical"
theme.layout_txt_fairh      = " ⁝ fair horizontal"
theme.layout_txt_spiral     = " ⁝ spiral"
theme.layout_txt_dwindle    = " ⁝ dwindle"
theme.layout_txt_max        = " ⁝ maximized"
theme.layout_txt_fullscreen = " ⁝ fullscreen"
theme.layout_txt_magnifier  = " ⁝ magnifier"
theme.layout_txt_floating   = " ⁝ floating"
-- and graphical
theme.layout_tile       = "/home/laite/.config/awesome/themes/default/layouts/tile.png"
theme.layout_tileleft   = "/home/laite/.config/awesome/themes/default/layouts/tileleft.png"
theme.layout_tilebottom = "/home/laite/.config/awesome/themes/default/layouts/tilebottom.png"
theme.layout_tiletop    = "/home/laite/.config/awesome/themes/default/layouts/tiletop.png"
theme.layout_fairv      = "/home/laite/.config/awesome/themes/default/layouts/fairv.png"
theme.layout_fairh      = "/home/laite/.config/awesome/themes/default/layouts/fairh.png"
theme.layout_spiral     = "/home/laite/.config/awesome/themes/default/layouts/spiral.png"
theme.layout_dwindle    = "/home/laite/.config/awesome/themes/default/layouts/dwindle.png"
theme.layout_max        = "/home/laite/.config/awesome/themes/default/layouts/max.png"
theme.layout_fullscreen = "/home/laite/.config/awesome/themes/default/layouts/fullscreen.png"
theme.layout_magnifier  = "/home/laite/.config/awesome/themes/default/layouts/magnifier.png"
theme.layout_floating   = "/home/laite/.config/awesome/themes/default/layouts/floating.png"
-- }}}

-- {{{ Titlebar
theme.titlebar_close_button_focus  = "/home/laite/.config/awesome/themes/zenburn/titlebar/close_focus.png"
theme.titlebar_close_button_normal = "/home/laite/.config/awesome/themes/zenburn/titlebar/close_normal.png"

theme.titlebar_ontop_button_focus_active  = "/home/laite/.config/awesome/themes/zenburn/titlebar/ontop_focus_active.png"
theme.titlebar_ontop_button_normal_active = "/home/laite/.config/awesome/themes/zenburn/titlebar/ontop_normal_active.png"
theme.titlebar_ontop_button_focus_inactive  = "/home/laite/.config/awesome/themes/zenburn/titlebar/ontop_focus_inactive.png"
theme.titlebar_ontop_button_normal_inactive = "/home/laite/.config/awesome/themes/zenburn/titlebar/ontop_normal_inactive.png"

theme.titlebar_sticky_button_focus_active  = "/home/laite/.config/awesome/themes/zenburn/titlebar/sticky_focus_active.png"
theme.titlebar_sticky_button_normal_active = "/home/laite/.config/awesome/themes/zenburn/titlebar/sticky_normal_active.png"
theme.titlebar_sticky_button_focus_inactive  = "/home/laite/.config/awesome/themes/zenburn/titlebar/sticky_focus_inactive.png"
theme.titlebar_sticky_button_normal_inactive = "/home/laite/.config/awesome/themes/zenburn/titlebar/sticky_normal_inactive.png"

theme.titlebar_floating_button_focus_active  = "/home/laite/.config/awesome/themes/zenburn/titlebar/floating_focus_active.png"
theme.titlebar_floating_button_normal_active = "/home/laite/.config/awesome/themes/zenburn/titlebar/floating_normal_active.png"
theme.titlebar_floating_button_focus_inactive  = "/home/laite/.config/awesome/themes/zenburn/titlebar/floating_focus_inactive.png"
theme.titlebar_floating_button_normal_inactive = "/home/laite/.config/awesome/themes/zenburn/titlebar/floating_normal_inactive.png"

theme.titlebar_maximized_button_focus_active  = "/home/laite/.config/awesome/themes/zenburn/titlebar/maximized_focus_active.png"
theme.titlebar_maximized_button_normal_active = "/home/laite/.config/awesome/themes/zenburn/titlebar/maximized_normal_active.png"
theme.titlebar_maximized_button_focus_inactive  = "/home/laite/.config/awesome/themes/zenburn/titlebar/maximized_focus_inactive.png"
theme.titlebar_maximized_button_normal_inactive = "/home/laite/.config/awesome/themes/zenburn/titlebar/maximized_normal_inactive.png"
-- }}}
-- }}}

return theme
