inherit ROOM;

void create()
{
        set("short", "Ӣ����¥");
        set("long", @LONG
�������ݳ����ľ�¥�����������Ĺ��Ͷ�Ҫ�ڴ�ЪЪ��
�Ⱥ��þơ�˵��׼���ύ��һ�������ѡ�����ͦ������������
�������м���������֡�Ҫ������С�ۣ�¥�ϻ�����������˵
¥�ϻ�����Ϣ�ң�ר��Ϊ����Щ�е�̰������׼���ġ�
LONG);

        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
         set("exits", ([
                "west" : __DIR__"wendingbei1",
                "east" : __DIR__"majiu",
                "up"   : __DIR__"yinghaoup",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
}