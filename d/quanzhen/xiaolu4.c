// xiaolu4.c ��ɽС·
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "��ɽС·");
        set("long", @LONG
�����Ǻ�ɽ�ϵ�С·������С·�������˹������޳����ģ�
Ҳ��ֻ����ǰ�Ĳ�ҩ�˲ȶ��ˣ��ֳ�����һ��С·�����ߵ����
�������·�ˡ�
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"xiaolu3",
                "north" : __FILE__,
                "south" : __DIR__"xiaolu8",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2680);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}