inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
这是一户普通的农家，屋里没有什么象样的摆设。墙边摆放着一
些农具，除此只外四壁皆空，看来并不富裕。 
LONG);

        set("exits", ([
                "north" : __DIR__"cun2",
        ]));
        set("objects", ([
                __DIR__"npc/cunmin": 1,
                __DIR__"npc/cunfu": 1,
        ]));

        setup();
        replace_program(ROOM);
}