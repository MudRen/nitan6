//Room: xiaojia-pianting.c

inherit ROOM;

void create ()
{
        set ("short", "ƫ��");
        set("long", @LONG
û����أ��Ǻǣ�
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/xiaojiadt",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yahuan" : 1,
        ]));

        set("coor/x", -10660);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}