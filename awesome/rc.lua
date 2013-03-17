-- Standard awesome library
require("awful")
require("awful.autofocus")
require("awful.rules")
-- Theme handling library
require("beautiful")
-- Notification library
require("naughty")

-- Load Debian menu entries
require("debian.menu")

-- {{{ Error handling
-- Check if awesome encountered an error during startup and fell back to
-- another config (This code will only ever execute for the fallback config)
if awesome.startup_errors then
    naughty.notify({ preset = naughty.config.presets.critical,
                     title = "Oops, there were errors during startup!",
                     text = awesome.startup_errors })
end

-- Handle runtime errors after startup
do
    local in_error = false
    awesome.add_signal("debug::error", function (err)
        -- Make sure we don't go into an endless error loop
        if in_error then return end
        in_error = true

        naughty.notify({ preset = naughty.config.presets.critical,
                         title = "Oops, an error happened!",
                         text = err })
        in_error = false
    end)
end
-- }}}

function updatelayoutbox(l, s)
	local screen = s or 1
	l.text = beautiful["layout_txt_" .. awful.layout.getname(awful.layout.get(screen))]
end


-- {{{ Variable definitions
-- Themes define colours, icons, and wallpapers
beautiful.init("/home/laite/.config/awesome/themes/laite_light.lua")
modkey = "Mod4"

terminal = "x-terminal-emulator"
terminal_tabbed = "urxvt -pe tabbedex"
editor = os.getenv("EDITOR") or "editor"
editor_cmd = terminal .. " -e " .. editor
gtkeditor = "gvim"
filemanager = "ranger"
filemanager_cmd = terminal .. " -e " .. filemanager
guifilemanager = "thunar"
webbrowser = "chromium-browser"

-- Table of layouts to cover with awful.layout.inc, order matters.
layouts =
{
    awful.layout.suit.floating,
    awful.layout.suit.tile,
    awful.layout.suit.tile.left,
    awful.layout.suit.tile.bottom,
    awful.layout.suit.tile.top,
    awful.layout.suit.spiral,
    awful.layout.suit.max
}
-- }}}

-- {{{ Tags
-- Define a tag table which hold all screen tags.
tags = {}
for s = 1, screen.count() do
	tags[s] = awful.tag({ "main", "www", "mail", "irc", "feed", "code", "m7", "m8", "m9", "float"}, s,
	{ 
		layouts[2], layouts[2], layouts[7],          -- Tags: 1, 2, 3
		layouts[5], layouts[2], layouts[5],          --       4, 5 ,6
		layouts[2], layouts[7], layouts[2],          --       7, 8, 9
		layouts[1]
	})
end
-- }}}


-- {{{ Wibox
mytextclock = awful.widget.textclock({ align = "right" }, "<span color='" .. theme.fg_normal .. "'>%a %d.%m.%Y,</span><span weight=\"bold\"> %H:%M  </span>")

gmb_box = widget({ type = "textbox" })
gmb_box.align = "center"
gmb_box.width = "1920"

mytimer = timer({ timeout = 5 })
mytimer:add_signal("timeout", function() 
	local line, last = ""
	local f = assert (io.popen ("cat /home/laite/.config/awesome/np_gmb"))
	  
	for line in f:lines() do last = line end -- there *really* shouldn't be more than one line in file
	f:close()
	-- plain & breaks textbox
	gmb_box.text = string.gsub(last, "&", "&amp;")
end)

mytimer:start()

-- Create a systray
mysystray = widget({ type = "systray" })

-- Create a wibox for each screen and add it
mywibox = {}
mypromptbox = {}
mylayoutbox = {}
mytaglist = {}
mytaglist.buttons = awful.util.table.join(
                    awful.button({ }, 1, awful.tag.viewonly),
                    awful.button({ modkey }, 1, awful.client.movetotag),
                    awful.button({ }, 3, awful.tag.viewtoggle),
                    awful.button({ modkey }, 3, awful.client.toggletag),
                    awful.button({ }, 4, awful.tag.viewprev),
                    awful.button({ }, 5, awful.tag.viewnext)
                    )
mytasklist = {}
mytasklist.buttons = awful.util.table.join(
                     awful.button({ }, 1, function (c)
                                              if c == client.focus then
                                                  c.minimized = true
                                              else
                                                  if not c:isvisible() then
                                                      awful.tag.viewonly(c:tags()[1])
                                                  end
                                                  -- This will also un-minimize
                                                  -- the client, if needed
                                                  client.focus = c
                                                  c:raise()
                                              end
                                          end),
                     awful.button({ }, 3, function ()
                                              if instance then
                                                  instance:hide()
                                                  instance = nil
                                              else
                                                  instance = awful.menu.clients({ width=250 })
                                              end
                                          end),
                     awful.button({ }, 4, function ()
                                              awful.client.focus.byidx(1)
                                              if client.focus then client.focus:raise() end
                                          end),
                     awful.button({ }, 5, function ()
                                              awful.client.focus.byidx(-1)
                                              if client.focus then client.focus:raise() end
                                          end))

for s = 1, screen.count() do
    -- Create a promptbox for each screen
    mypromptbox[s] = awful.widget.prompt({ layout = awful.widget.layout.horizontal.leftright })
    -- Create an imagebox widget which will contains an icon indicating which layout we're using.
    -- We need one layoutbox per screen.

	txtlayoutbox = widget({ type = "textbox" })
    txtlayoutbox.text = beautiful["layout_txt_" .. awful.layout.getname(awful.layout.get(s))] 
    awful.tag.attached_add_signal(s, "property::selected", function ()
        updatelayoutbox(txtlayoutbox, s) 
    end)
    awful.tag.attached_add_signal(s, "property::layout", function ()
        updatelayoutbox(txtlayoutbox, s) 
    end)

    mylayoutbox[s] = awful.widget.layoutbox(s)
    mylayoutbox[s]:buttons(awful.util.table.join(
                           awful.button({ }, 1, function () awful.layout.inc(layouts, 1) end),
                           awful.button({ }, 3, function () awful.layout.inc(layouts, -1) end),
                           awful.button({ }, 4, function () awful.layout.inc(layouts, 1) end),
                           awful.button({ }, 5, function () awful.layout.inc(layouts, -1) end)))
    -- Create a taglist widget
    mytaglist[s] = awful.widget.taglist(s, awful.widget.taglist.label.all, mytaglist.buttons)

    -- Create a tasklist widget
    mytasklist[s] = awful.widget.tasklist(function(c)
                                              return awful.widget.tasklist.label.currenttags(c, s)
                                          end, mytasklist.buttons)

    -- Create the wibox
    mywibox[s] = awful.wibox({ position = "top", screen = s })
    -- Add widgets to the wibox - order matters
    mywibox[s].widgets = {
        {
            --mylauncher,
            mytaglist[s],
			txtlayoutbox,
            mypromptbox[s],
            layout = awful.widget.layout.horizontal.leftright
        },
        --mylayoutbox[s],
        mytextclock,
        s == 1 and mysystray or nil,
		gmb_box,
        layout = awful.widget.layout.horizontal.rightleft
    }
end
-- }}}

-- {{{ Mouse bindings
root.buttons(awful.util.table.join(
    --awful.button({ }, 3, function () mymainmenu:toggle() end),
    awful.button({ }, 4, awful.tag.viewprev),
    awful.button({ }, 5, awful.tag.viewnext)
))
-- }}}

-- {{{ Key bindings
globalkeys = awful.util.table.join(
    awful.key({ modkey,           }, "h",   awful.tag.viewprev       ),
    awful.key({ modkey,           }, "l",  awful.tag.viewnext       ),
    awful.key({ modkey,           }, "Left",   awful.tag.viewprev       ),
    awful.key({ modkey,           }, "Right",  awful.tag.viewnext       ),
    awful.key({ modkey,           }, "^", awful.tag.history.restore),

    awful.key({ modkey,           }, "j",
        function ()
            awful.client.focus.byidx( 1)
            if client.focus then client.focus:raise() end
        end),
    awful.key({ modkey,           }, "k",
        function ()
            awful.client.focus.byidx(-1)
            if client.focus then client.focus:raise() end
        end),
    --awful.key({ modkey,           }, "w", function () mymainmenu:show({keygrabber=true}) end),

    -- Layout manipulation
    awful.key({ modkey, "Shift"   }, "j", function () awful.client.swap.byidx(  1)    end),
    awful.key({ modkey, "Shift"   }, "k", function () awful.client.swap.byidx( -1)    end),
    awful.key({ modkey, "Control" }, "j", function () awful.screen.focus_relative( 1) end),
    awful.key({ modkey, "Control" }, "k", function () awful.screen.focus_relative(-1) end),
    awful.key({ modkey,           }, "u", awful.client.urgent.jumpto),
    awful.key({ modkey,           }, "Tab",
        function ()
            awful.client.focus.history.previous()
            if client.focus then
                client.focus:raise()
            end
        end),

	-- hide/show wibox
	awful.key({ modkey }, "b", function ()
		mywibox[mouse.screen].visible = not mywibox[mouse.screen].visible
	end),

	-- helpers
	awful.key({ }, "XF86AudioPlay", function () awful.util.spawn("gmusicbrowser -cmd PlayPause") end),
	awful.key({ }, "XF86AudioStop", function () awful.util.spawn("gmusicbrowser -cmd Stop") end),
    awful.key({ }, "XF86AudioNext", function () awful.util.spawn("gmusicbrowser -cmd NextSong") end),
    awful.key({ }, "XF86AudioPrev", function () awful.util.spawn("gmusicbrowser -cmd PrevSong") end),

    -- Standard programs
    awful.key({ modkey,           }, "Return", function () awful.util.spawn(terminal) end),
    awful.key({ modkey,           }, "d", function () awful.util.spawn("dmenu_run -i -fn '-*-fixed-medium-r-*-*-*-100-100-100-c-*-iso10646-*' -m 0 -nb \"#3f3f3f\" -nf \"#dcdccc\" -sb \"#1e2320\" -sf \"#ececac\" ") end),
    awful.key({ modkey,           }, "e", function () awful.util.spawn("xfce4-appfinder") end),
    awful.key({ modkey,           }, "t", function () awful.util.spawn(guifilemanager) end),
    awful.key({ modkey,           }, "v", function () awful.util.spawn(gtkeditor) end),
    awful.key({ modkey,           }, "u", function () awful.util.spawn(terminal_tabbed) end),
    awful.key({ modkey,           }, "p", function () awful.util.spawn(filemanager_cmd) end),
    awful.key({ modkey,           }, "i", function () awful.util.spawn(webbrowser) end),

    awful.key({ modkey, "Control" }, "r", awesome.restart),
    awful.key({ modkey, "Shift"   }, "q", awesome.quit),

    awful.key({ modkey, "Shift"   }, "Right", function () awful.tag.incmwfact( 0.05)    end),
    awful.key({ modkey, "Shift"   }, "Left",  function () awful.tag.incmwfact(-0.05)    end),
    awful.key({ modkey,           }, "Up",    function () awful.client.incwfact( 0.05)    end),
    awful.key({ modkey,           }, "Down",  function () awful.client.incwfact(-0.05)    end),
    awful.key({ modkey, "Shift"   }, "h",     function () awful.tag.incnmaster( 1)      end),
    awful.key({ modkey, "Shift"   }, "l",     function () awful.tag.incnmaster(-1)      end),
    awful.key({ modkey, "Control" }, "h",     function () awful.tag.incncol( 1)         end),
    awful.key({ modkey, "Control" }, "l",     function () awful.tag.incncol(-1)         end),
    awful.key({ modkey,           }, "space", function () awful.layout.inc(layouts,  1) end),
    awful.key({ modkey, "Shift"   }, "space", function () awful.layout.inc(layouts, -1) end),
    awful.key({ modkey, "Control" }, "n", awful.client.restore),

    -- Prompt
    awful.key({ modkey },            "r",     function () mypromptbox[mouse.screen]:run() end),

    awful.key({ modkey }, "x",
              function ()
                  awful.prompt.run({ prompt = "Run Lua code: " },
                  mypromptbox[mouse.screen].widget,
                  awful.util.eval, nil,
                  awful.util.getdir("cache") .. "/history_eval")
              end)
)

clientkeys = awful.util.table.join(
    awful.key({ modkey,           }, "f",      function (c) c.fullscreen = not c.fullscreen  end),
    awful.key({ modkey, "Shift"   }, "c",      function (c) c:kill()                         end),
    awful.key({ modkey, "Control" }, "space",  awful.client.floating.toggle                     ),
    awful.key({ modkey,           }, "w", function (c) c:swap(awful.client.getmaster()) end),
    awful.key({ modkey,           }, "o",      awful.client.movetoscreen                        ),
    awful.key({ modkey, "Shift"   }, "r",      function (c) c:redraw()                       end),
    awful.key({ modkey, "Shift"   }, "t",      function (c) c.ontop = not c.ontop            end),
    awful.key({ modkey,           }, "n",
        function (c)
            c.maximized_horizontal = not c.maximized_horizontal
            c.maximized_vertical   = not c.maximized_vertical
        end)
)

-- Compute the maximum number of digit we need, limited to 9
keynumber = 0
for s = 1, screen.count() do
   keynumber = math.min(9, math.max(#tags[s], keynumber));
end

-- Bind all key numbers to tags.
-- Be careful: we use keycodes to make it works on any keyboard layout.
-- This should map on the top row of your keyboard, usually 1 to 9.
for i = 1, keynumber do
    globalkeys = awful.util.table.join(globalkeys,
        awful.key({ modkey }, "#" .. i + 9,
                  function ()
                        local screen = mouse.screen
                        if tags[screen][i] then
                            awful.tag.viewonly(tags[screen][i])
                        end
                  end),
        awful.key({ modkey, "Control" }, "#" .. i + 9,
                  function ()
                      local screen = mouse.screen
                      if tags[screen][i] then
                          awful.tag.viewtoggle(tags[screen][i])
                      end
                  end),
        awful.key({ modkey, "Shift" }, "#" .. i + 9,
                  function ()
                      if client.focus and tags[client.focus.screen][i] then
                          awful.client.movetotag(tags[client.focus.screen][i])
                      end
                  end),
        awful.key({ modkey, "Control", "Shift" }, "#" .. i + 9,
                  function ()
                      if client.focus and tags[client.focus.screen][i] then
                          awful.client.toggletag(tags[client.focus.screen][i])
                      end
                  end))
end

-- bind 0 to tag 10
if (#tags[1] > 9) then
    globalkeys = awful.util.table.join(globalkeys,
        awful.key({ modkey }, "0",
                  function ()
                        local screen = mouse.screen
                        if tags[screen][10] then
                            awful.tag.viewonly(tags[screen][10])
                        end
                  end),
        awful.key({ modkey, "Control" }, "0",
                  function ()
                      local screen = mouse.screen
                      if tags[screen][10] then
                          awful.tag.viewtoggle(tags[screen][10])
                      end
                  end),
        awful.key({ modkey, "Shift" }, "0",
                  function ()
                      if client.focus and tags[client.focus.screen][10] then
                          awful.client.movetotag(tags[client.focus.screen][10])
                      end
                  end),
        awful.key({ modkey, "Control", "Shift" }, "0",
                  function ()
                      if client.focus and tags[client.focus.screen][10] then
                          awful.client.toggletag(tags[client.focus.screen][10])
                      end
                  end))
end

clientbuttons = awful.util.table.join(
    awful.button({ }, 1, function (c) client.focus = c; c:raise() end),
    awful.button({ modkey }, 1, awful.mouse.client.move),
    awful.button({ modkey }, 3, awful.mouse.client.resize))

-- Set keys
root.keys(globalkeys)
-- }}}

-- {{{ Rules
awful.rules.rules = {
    -- All clients will match this rule.
    { rule = { },
      properties = { border_width = beautiful.border_width,
                     border_color = beautiful.border_normal,
                     focus = true,
					 size_hints_honor = false,
                     keys = clientkeys,
                     buttons = clientbuttons } },
    { rule = { class = "Xfce4-terminal" },
      properties = { border_color = beautiful.border_terminal } },
    { rule = { class = "Xfce4-appfinder" },
      properties = { floating = true } },
    { rule = { class = "Timetracker" },
      properties = { floating = true } },
    { rule = { class = "Firefox" },
      properties = { floating = false } },
    { rule = { class = "File-roller" },
      properties = { floating = true } },
    { rule = { class = "Xarchiver" },
      properties = { floating = true } },
    { rule = { class = "MPlayer" },
      properties = { floating = true } },
    { rule = { class = "gimp" },
      properties = { floating = true } },
    { rule = { name = "Searching for a picture of"},
      properties = { floating = true } },
    { rule = { name = "Progress"},
      properties = { floating = true } },
    { rule = { name = "Edit Multiple Songs Properties"},
      properties = { floating = true } },
    { rule = { role = "D_laite_timebard"},
      properties = { focus = false } },
    { rule = { class = "Thunderbird" },
      properties = { border_width = "0", tag = tags[1][3] } },
    -- { rule = { class = "Firefox" },
    --   properties = { tag = tags[1][2] } },
}
-- }}}

-- {{{ Signals
-- Signal function to execute when a new client appears.
client.add_signal("manage", function (c, startup)
    -- Add a titlebar
    -- awful.titlebar.add(c, { modkey = modkey })

    -- Enable sloppy focus
    c:add_signal("mouse::enter", function(c)
        if awful.layout.get(c.screen) ~= awful.layout.suit.magnifier
            and awful.client.focus.filter(c) then
            client.focus = c
        end
    end)

    if not startup then
        -- Set the windows at the slave,
        -- i.e. put it at the end of others instead of setting it master.
        -- awful.client.setslave(c)

        -- Put windows in a smart way, only if they does not set an initial position.
        if not c.size_hints.user_position and not c.size_hints.program_position then
            awful.placement.under_mouse(c)
            awful.placement.no_offscreen(c)
        end
    end
end)

client.add_signal("focus", function(c) 
	if c.class == "Xfce4-terminal" then
		c.border_color = theme.border_terminal_focus
	else
		c.border_color = theme.border_focus
	end
end)
client.add_signal("unfocus", function(c)
	if c.class == "Xfce4-terminal" then
		c.border_color = theme.border_terminal
	else
		c.border_color = beautiful.border_normal
	end
end)

-- Startup commands 
awful.util.spawn("sh /home/laite/bin/xmodmaps.sh")
awful.util.spawn("numlockx on")
awful.util.spawn("xset s off -dpms")
-- use xfce settings to get proper settings for fonts and themes
awful.util.spawn("xfsettingsd")
-- manage volume keys easily
awful.util.spawn("xfce4-volumed")
-- }}}
