#include <ansi.h>

inherit ITEM;

void init()
{
    set("no_get", "���ò�����������������������(dig)��\n");
    set("no_give","��ô����ҩ�����������ˣ�\n");
    set("no_drop","��ô����ĵ�ҩ�����˶��ϧѽ��\n");
    set("no_sell","��������֪��"+query("name", this_object())+"�ļ�ֵ�������Լ����Űɡ�\n");

    add_action("do_dig", "dig");
    add_action("do_eat", "eat");
}

void create()
{
  set_name(RED "������ѿ" NOR, ({"qiong cao","cao"}));
  set_weight(200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "һ���Ϻ�ɫ��С�ݡ�\n");
    set("value", 0);
    set("drug_type", "��Ʒ");
  }
  
  // the following line is added by snowcat
  set("is_monitored",1);
  setup();
}
int do_dig(string arg)
{
   object spirit, who, me, where;
   who=this_player();
   me=this_object();
   where=environment(me);

   if( query("can_eat", me) )
     return notify_fail("ʲô��\n");

   if( !arg || (arg!="qiong cao" && arg!="cao"))
     return notify_fail("��Ҫ��ʲô��\n");

   if(who->is_fighting() && who->is_busy())
     return notify_fail("���æ��ûʱ���ڲݡ�\n"); 

   if( spirit=present("spirit")){
     message_vision("�չ⾫�����ܹ�â��ʢ����$N�����˹�����\n", who);
     spirit->kill_ob(who);
     who->fight_ob(spirit);
     return 1;
   }
     message_vision("$N���Ὣ$n����������\n", who, me);
     set("can_eat", 1, me);
     me->move(who);
   tell_object(who, HIY "\n\n�չ⾫�黯ΪһƬ�����Ĺ�â���������ӡ�⿪�ˣ�\n"NOR);  
   message("channel:chat",HBMAG"��������硿"+query("name", me)+"�ɹ��Ľ⿪�˵����ӡ.\n"NOR,users());
        set_temp("m_success/����", 1, me);
     remove_call_out("grow_a");
     remove_call_out("grow_b");
                remove_call_out("grow_c");
                remove_call_out("grow_d");
                remove_call_out("grow_e");
                remove_call_out("grow_f");
                remove_call_out("grow_g");
     delete("grow_grass", where);

   if( !spirit && query("eatable", me)){
     seteuid(getuid());
     spirit=new("/quest/tulong/npc/spirit1");
     spirit->move(environment(who));
   tell_room(environment(who), "��Ȼ��â��ʢ���չ⾫����������˳�����\n");
   spirit->kill_ob(who);
   who->fight_ob(spirit);
   }
   return 1;
}

int do_eat(string arg)
{
   object me=this_object();
   object who=this_player();
   int neili_add;
   
     if (!id(arg))
         return notify_fail("��Ҫ��ʲô��\n");
   if( !query("can_eat", me) )
     return notify_fail("��Ҫ��ʲô��\n");

   set("food", who->max_food_capacity(), who);
     set("water", who->max_water_capacity(), who);

   if( !query("eatable", me)){
     message_vision("$N���̻��ʰ�ؽ�һ��$n������ȥ��\n", who, me);
     destruct(me);
     return 1;
   }

   neili_add=30;
   
   message_vision("$N��һ��$n������������˶ǣ����Ϸ�������Ρ�\n", who, me);
   tell_object(who, "�����һ������ֱͨ���ϣ��������º�����ʹ�����������\n");

  set("eff_jing",query("max_jing",  who), who);
  set("jing",query("max_jing",  who), who);
  set("eff_qi",query("max_qi",  who), who);
  set("qi",query("max_qi",  who), who);
   
   if( query("max_neili", who)<10*who->query_skill("force")){
         addn("max_neili", neili_add, who);
   }
     destruct(me);
}



void invocation()
{
   object me=this_object();
   int i=200+random(200);
   call_out("grow_a", i, me);
}

int grow_a(object me)
{
   int i=400+random(400);
   tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
   set_name(RED "һҶ����" NOR, ({"qiong cao","cao"}));
   call_out("grow_b", i, me);
   return 1;
}

int grow_b(object me)
{
        int i=600+random(600);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
        set_name(RED "��Ҷ����" NOR, ({"qiong cao","cao"}));
        call_out("grow_c", i, me);
        return 1;
}

int grow_c(object me)
{
        int i=800+random(800);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
        set_name(RED "��Ҷ����" NOR, ({"qiong cao","cao"}));
        call_out("grow_d", i, me);  
        return 1;
}

int grow_d(object me)
{
        int i=1000+random(1000);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
        set_name(RED "��Ҷ����" NOR, ({"qiong cao","cao"}));
        call_out("grow_e", i, me);  
        return 1;
}

int grow_e(object me)
{
        int i=1200+random(1000);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
        set_name(RED "��Ҷ����" NOR, ({"qiong cao","cao"}));
        call_out("grow_f", i, me);  
        return 1;
}

int grow_f(object me)
{
        int i=1500+random(1000);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
        set_name(RED "��Ҷ����" NOR, ({"qiong cao","cao"}));
        call_out("grow_g", i, me);  
        return 1;
}

int grow_g(object me)
{
        int i=2000+random(1000);
        tell_room(environment(me), me->name()+"�����س�����һ��СҶ��\n", ({me, me}));
   tell_room(environment(me), me->name()+"��Χ��������һ�ɺ�⡣\n", ({me, me}));
        set_name(RED "��Ҷ��֥��" NOR, ({"qiong cao","cao"}));
   set("eatable",1);
        return 1;
}