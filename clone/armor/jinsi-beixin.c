

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY "��˿����" NOR, ({ "jinsi beixin", "jinsi", "beixin" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 500);
                set("limit", ([
                        "exp"  :  500000,
                        "int"  :  30,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
