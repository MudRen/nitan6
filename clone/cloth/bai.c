// bai.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("����", ({"bai pao", "white cloth", "cloth"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("long", "һ��ѩ�׵Ĳ��ۣ�һ˿��ɫҲû�У�\n");
                set("unit", "��");
                set("value", 200);
                set("armor_prop/armor", 5);

        }
        setup();
}