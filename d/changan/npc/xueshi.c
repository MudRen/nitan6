//xueshi.c

inherit NPC;

void create()
{
        set_name("�Ԩ", ({"li boyuan", "li", "boyuan"}));
        set("gender", "����");
        set("age", 45);
        set("title", "��ѧʿ");
        set("str", 25);
        set("int", 30);
        set("long", "�Ԩ�ǹ��Ӽ��ѧʿ��\n");
        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("class", "scholar");
        set_skill("unarmed", 50);
        set_skill("dodge",50);
        set_skill("literate", 400);
        set_skill("parry", 50);

        set("neili", 500); 
        set("max_neili", 500);
        set("inquiry", ([
                "����ʶ��": "���ˣ��������Եط��ˣ�\n",
                "ѧϰ" : "ѧϰ��Ҫ��ѧ�ѵ�\n",
        ]) );

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

int recognize_apprentice(object ob)
{
        if( query_temp("mark/��", ob)<1 )
                return 0;
        addn_temp("mark/��", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/��", who) )
        set_temp("mark/��", 0, who);
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("�Ԩͬ��ָ��$NһЩ����д�ֵ����⡣\n", who);
                addn_temp("mark/��", ob->value()/50, who);
        
                return 1; 
        }
}