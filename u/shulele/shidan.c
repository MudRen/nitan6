
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"尸丹"NOR, ({ "shi dan","dan" }));
   set_weight(100);
   set("unit", "颗");
   set("long","这是一颗由尸体练成的丹药,服用(fu dan)后，会发生什么事情呢?\n");
   set("value", 0);
   set("no_give",1);
   set("no_save",1);
}

void init()
{
	add_action("do_fu","fu");
}
int do_fu(string arg)
{
	object me,ob;int i;
	ob=this_object();me=this_player();
	if(!arg||(arg!="dan"&&arg!="丹"))
		return notify_fail("你要服用什么?\n");
	message_vision("$N服下了一颗[尸丹].\n",me);
if(random(10)>8)
{
message_vision("$N感觉到神清气爽，内力似乎增加了。\n",me);
me->add("max_force",10);
}else{
me->set("gin",-1);
	destruct(ob);
	return 1;
}
}