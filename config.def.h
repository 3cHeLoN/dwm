/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:size=13",
                                        "JoyPixels:size=13:antialias=true:autohint=true"
										};

static const char dmenufont[]       = "monospace:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#4C566A"; //"#005577";
static const char col_border[] = "#458588";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan,  col_border  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          -1 },
	{ "st",      NULL,     NULL,           0,         0,          -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          -1 }, /* xev */
    { NULL, "sun-awt-X11-XFramePeer",   NULL,         0,          1,           -1 },
    { NULL, "sun-awt-XDialogPeer",   NULL,         0,          1,           -1 },
	{ "st-256color", NULL, NULL,           0,         0,          -1 }, // st
    { "matplotlib",  NULL, NULL,           0,         1,          -1 },   
    { "Microsoft Teams - Preview", NULL, "Microsoft Teams Notification", 0, 1, -1},
    { "firefox", "Toolkit", NULL, 0, 1, -1 },
    { "Lxappearance", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-i", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = {"rofi", "-show", "drun", "-show-icons", NULL};
//static const char *dmenudesktopcmd[] = { "/home/folkert/.local/bin/run_dmenu_desktop", NULL };
static const char *passmenucmd[] = {"passmenu", "-i", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *lockcmd[] = {"slock", NULL};
static const char *amixerpluscmd[] = {"/home/folkert/.local/bin/audio_plus.sh" , NULL };
static const char *amixermincmd[] = {"/home/folkert/.local/bin/audio_min.sh", NULL };
static const char *amixertogglecmd[] = {"/home/folkert/.local/bin/audio_toggle.sh", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *mpd_togglecmd[] = {"mpc", "toggle", NULL};
static const char *mpd_nextcmd[] = {"mpc", "next", NULL};
static const char *mpd_prevcmd[] = {"mpc", "prev", NULL};
static const char *email_cmd[] = {"st", "-e", "neomutt", NULL};
static const char *dmenuemocmd[] = {"/home/folkert/.local/bin/dmenuunicode", NULL};
static const char *newsboatcmd[] = {"setsid", "st", "-e", "newsboat", NULL};
static const char *youtubecmd[] = {"setsid", "st", "-e", "newsboat", "--config-file=/home/folkert/.config/newsboat/youtube-config", "--url-file=/home/folkert/.config/newsboat/youtube-urls", "--cache-file=/home/folkert/.config/newsboat/youtube-cache.db", NULL };
static const char *browsercmd[] = {"brave", "--use-gl=desktop", "--enable-features=VaapiVideoDecoder", NULL };
static const char *recordcallcmd[] = { "/home/folkert/.local/bin/toggle_call_record", "/home/folkert/Audio", NULL };
static const char *filebrowsecmd[] = { "st", "-e", "vifmrun", NULL };
static const char *mymenucmd[] = { "run_xmenu", NULL };
static const char *exposecmd[] = { "skippy-xd", NULL };
static const char *nautiluscmd[] = { "nautilus", NULL };
static const char *wallpapercmd[] = { "switch_wallpaper.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_w,      spawn,          {.v = wallpapercmd }},
    { MODKEY,                       XK_s,      spawn,          {.v = exposecmd }},
    { MODKEY,                       XK_y,      spawn,          {.v = youtubecmd }},
    { MODKEY,                       XK_n,      spawn,          {.v = newsboatcmd }},
    { MODKEY,                       XK_u,      spawn,          {.v = dmenuemocmd }},
    { MODKEY,                       XK_e,      spawn,          {.v = nautiluscmd }},
    { MODKEY,                       XK_r,      spawn,          {.v = recordcallcmd }},
    { MODKEY,                       XK_v,      spawn,          {.v = filebrowsecmd }},
    { MODKEY|ControlMask,           XK_p,      spawn,          {.v = mpd_togglecmd }},
    { MODKEY|ControlMask,           XK_period, spawn,          {.v = mpd_nextcmd }},
    { MODKEY|ControlMask,           XK_comma,  spawn,          {.v = mpd_prevcmd }},
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_bracketleft, spawn,     {.v = amixermincmd } },
    { Mod1Mask|ControlMask,         XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_bracketright, spawn,    {.v = amixerpluscmd } },
	{ MODKEY|ShiftMask,             XK_bracketright, spawn,    {.v = amixertogglecmd } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_bracketleft, spawn,     {.v = amixertogglecmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    //{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	//{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	//{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkRootWin,           0,              Button3,        spawn,          {.v = mymenucmd }},
};

