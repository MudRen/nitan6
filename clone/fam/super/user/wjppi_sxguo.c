#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "鼠仙果" NOR, ({"shuxianguo"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "传说鼠仙果乃田鼠偷吃了蓬莱仙果后，钻入地底死亡，经数百年生长而成。\n" + 
        	                "服食(fushi shuxianguo)后可永久提升气血上限20点。\n" HIC
        	                "拥有者：wjppi\n" NOR);
                set("unit", "颗");
                set("owner", "wjppi"); // 绑定拥有者
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "fushi");       
}

int do_use(string arg)
{
	object ob, me;
	
	me = this_player();

	if (! arg || arg != query("id"))
		return notify_fail("你要服食什么？\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这个东西！\n");

	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "已经于其他玩家绑定！\n");
	
	me->add("drug_addqi", 20);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，提升气血上限20点！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + "。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}