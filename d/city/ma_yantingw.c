inherit ROOM;

void create()
{
        set("short", "��ׯ����");
        set("long", @LONG
��������ׯ�����������õ���Ϊ���ţ�˿��û�������ϵ�
�������ա�һ�ź�ľ���������и���񣬹�����˸�ʽ������
�顣����ؤ�����ؤΧ�������
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "east"  : __DIR__"ma_zhengting",
        ]));
        set("objects", ([
                "/d/gaibang/npc/2dai" : 1,
                "/d/gaibang/npc/3dai" : 1,
                "/d/gaibang/npc/4dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}