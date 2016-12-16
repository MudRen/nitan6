// hua4.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIC "翡翠兰" NOR, ({"feicui lan", "feicui", "lan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "朵");
		set("long", "这是一朵千年难得一见的翡翠兰，据说能解百毒。\n");
        	set("value", 1000000);
		set("only_do_effect", 1);
	}
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/feicui", me)<300 ) 
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n"); 
                return 1; 
        }

        set_temp("last_eat/feicui", time(), me); 
set_temp("nopoison", 3, 	me);
set("eff_jing",query("max_jing",  me), 	me);
set("jing",query("max_jing",  me), 	me);
set("eff_qi",query("max_qi",  me), 	me);
set("qi",query("max_qi",  me), 	me);
        message_vision("$N把" + name() + "扔进嘴里，几下就吞了下去。\n", me);
	tell_object(me, HIG "\n你只觉一股清香沁入心肺，顿时灵台一片"
		        "空明，神意清爽！\n" NOR);
	destruct(this_object());
	return 1;
}
