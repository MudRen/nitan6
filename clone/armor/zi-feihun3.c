#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name( NOR + MAG "���׷ɻ�" NOR, ({ "zilei feihun3", "zilei" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("value", 2000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/int", 8);
                                set("armor_prop/con", 8);
                                set("armor_prop/damage", 400);
                                set("limit", ([ 
                                        "exp" : 85000000,
                                        "scborn" : 1,
                                ]));
                set("material", "gold");
        }
        setup();
}

int query_autoload()
{
        return 1;
}