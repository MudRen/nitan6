//Room: /d/dali/xingyunhu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","���ƺ���");
        set("long",@LONG
���ƺ�����С��������Բ��ʮ���������ϼɽ����ˮ�峺����
�����ģ����Ǵ�����������������֮ҹ������¹�ӳ�պ��棬���
ˮ����ҡҷ���ˣ��緱��������У��������ƣ�����֮���ڴ�Զ����
֮���ϰ����ɼ�����������з����������С�
LONG);
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "north"    : __DIR__"buxiongbu",
            "eastup"   : __DIR__"yuxiashan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19020);
	set("coor/y", -6920);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}