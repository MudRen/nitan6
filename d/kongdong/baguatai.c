
inherit ROOM;
#include <room.h>
#include <ansi.h>



void create()
{
	set("short", YEL"八卦台"NOR);
	set("long",@LONG
这里是倥侗派木灵子亲自打造的铜制的八卦台，铜台上刻有一个巨大的
八卦图案。按照子、丑、寅、卯、辰、巳、午、未、申、酉、戌、亥的方位
排布。倥侗弟子可以来这里掐算占卜，非常灵验。
LONG);
    set("need_clean", "崆峒派");
	set("exits",
	([
             "down" : __DIR__"18_yuan",
          	]));
    setup();

}
