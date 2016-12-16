
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIR "����" NOR, ({ "tian ming2", "tian", "ming2" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 200);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 7);
                set("armor_prop/str", 6);
                set("armor_prop/int", 4);
                set("limit", ([ 
                                        "exp" : 15000000,
                                        "scborn" : 1,
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}