//  Room:  /d/lanzhou/road3.c

inherit  ROOM;

void  create  ()
{
        set("short",  "�����");
        set("long",  @LONG
����һ����������ʯ��ֵ����ӱ���һֱ�������졣����·������
��ʱ�й��������߹����͸ղų�������ľ����γ������Աȡ��ϱ��ǳ�
�����Ĵ��------���Ӵ�֡�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"northgate",
                "south" : __DIR__"street2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}