inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "������");
        set("long", @LONG
�����ǰ��һ����ľ��ï�ĸ�ɽ������ɽ������������Լ�ɼ���
һ��ʯ����ɽ�����죬���ż�������͡�һ������������¥ʽ��ʯ��
��ɽ�������������С������������ĸ����֣�ԭ�����������������
�䵱ɽ���䵱ɽһ��̫��ɽ��Ϊ��ʮ������֮һ���ж�ʮ�߷塢��ʮ
���ҡ���ʮ�Ľ�����̨���微����̶�������š��������һ���أ���
��������ɭ�ޣ����ղ��쾰���ľ���
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/zhike": 1,
                CLASS_D("wudang") + "/daotong": 2,
        ]));
        set("outdoors", "wudang");
        set("exits", ([
                "east"     : __DIR__"slxl3",
                "southup"  : __DIR__"shijie1",
        ]));
        set("coor/x", -370);
        set("coor/y", -180);
        set("coor/z", 20);
        setup();
}