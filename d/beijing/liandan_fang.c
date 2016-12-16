#include <ansi.h>
inherit ROOM;

#define DAN_DIR         "/d/beijing/npc/dan/"

int do_liandan(string arg);

void create()
{       set("short", HIY "������" NOR);
        set("long", @LONG
����Ҧ���������������ܶѷ���������ҩ�ģ�һ����ڵ�����¯
(lu)���������룬���е�ҩζ���ò�ɢ����������һ��ɢ�����ĵ���
ɫ��������ʱ��ĵ�ҩ�����Ѿ������������������ص�ɫ�ʡ�
LONG );
        set("no_fight", 1);
        set("item_desc", ([
                "lu" : YEL "һ�����ɫ�Ĵ�����¯��������ͣ������˿˿���̡�\n" NOR,
        ]));

        set("exits", ([
                "south" : __DIR__"liandan_yaoshi",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_liandan", "liandan"); 
}

int do_liandan(string arg)
{
        int time;

        object me = this_player();
        time = 5 + random(5);

        if (me->is_busy())
                return notify_fail("�����п�����˵�ɡ�\n");

        if( query_temp("liandan", me)<1 )
                return notify_fail("����֮�أ��������š�\n");

        if( query_temp("liandan", me)<2 )
                return notify_fail("ԭ�϶�û�У���ʲô����\n");

        if( query_temp("liandan", me) == 3 )
                return notify_fail("��ҩ�����У�������ġ�\n");

        if( query_temp("liandan", me) == 4 )
                return notify_fail("���Ƴɹ�����ȥ�����ɡ�\n");

        if( query("jing", me)<80 || 
            query("qi", me)<80 )
                return notify_fail("�����ڵľ���״���޷����Ƶ�ҩ��\n");

        message_vision(HIY "$N" HIY "��ԭ��ҩ��һһ�Ž�¯�У���"
                       "�����£���Ŀ������\n" NOR, me); 
        set_temp("liandan", 3, me);
        me->start_call_out((: call_other, __FILE__, "liandan", me :), time);
        me->start_busy(time);
        return 1;
}

// ���ⵤ�б�
string *SM_LIST = ({ "danS_1", "danS_2", "danS_3", "danS_4", "danS_5",
                     "danM_3", "danM_4", "danM_5", "danM_7", "danM_8",
                     "danM_9", "danB_6", "danC_5", "danD_6", });

// ��ͨ���б�
string *NORMAL_LIST = ({ "danM_1", "danM_2", "danM_6",
                         "danA_1", "danA_2", "danA_3", "danA_4", "danA_5",
                         "danB_1", "danB_2", "danB_3", "danB_4", "danB_5",
                         "danC_1", "danC_2", "danC_3", "danC_4",
                         "danD_1", "danD_2", "danD_3", "danD_4", "danD_5", });

void liandan(object me)
{
        object ob;
        int skill;

        skill = (int)me->query_skill("liandan-shu", 1);

        if (environment(me) != this_object())
                return;

        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));
        if (random(skill) < 60 && random(3) == 1) 
        {
                set_temp("liandan", 1, me);
                message_vision(HIR "����$N" HIR "���Ȼ��ʱ��һ��̱�"
                               "����ζ��¯�г����$N" HIR "��æ��¯ȡҩ��"
                               "�����Ū�ø���ͷ������\n"NOR,me);
        } else
        if (random(skill) > 60 && random(10) == 1)
        {
                message_vision(HIY "¯�����̽���ת������Ȼһ�����������$N"
                               HIY "��������һ������ʱ��ҩ��ζ��Ũ��$N"
                               HIY "�Ͻ������ƶ��ɵĵ���ȡ����\n" NOR, me);
                set_temp("liandan", 4, me);
                ob = new(DAN_DIR + SM_LIST[random(sizeof(SM_LIST))]);
                tell_object(me, HIC "����������Ʒ��" + NOR + ob->name() + NOR + HIC "����\n" NOR);
                ob->move(me, 1);
                
/*
                if( stringp(query("family/family_name", me)) )
                {                        
                        addn("family/gongji", 10+random(12), me);
                        tell_object(me, HIC "������ɹ���������Ʒ��ҩ������ʦ�ŵĹ�������ˣ�\n" NOR);
                }
*/
                
                if (me->can_improve_skill("liandan-shu") && skill < 300)
                {
                        me->improve_skill("liandan-shu",query("int", me)+10);
                        tell_object(me, HIC "��������������ġ�������������ˣ�\n" NOR);
                }
        } else
        {
                message_vision(HIC "¯�����̽���ת������ҩ��ζ��Ũ��$N"
                               HIC "���˵ذ����ƶ��ɵĵ���ȡ����\n" NOR, me);
                set_temp("liandan", 4, me);
                ob = new(DAN_DIR + NORMAL_LIST[random(sizeof(NORMAL_LIST))]);
                tell_object(me, HIC "�������ˡ�" + NOR + ob->name() + NOR + HIC "����\n" NOR);
                ob->move(me, 1);

/*
                if( stringp(query("family/family_name", me)) )
                {                        
                        addn("family/gongji", 5+random(6), me);
                        tell_object(me, HIC "������ɹ���������ҩ������ʦ�ŵĹ�������ˣ�\n" NOR);
                }
*/
                
                if (me->can_improve_skill("liandan-shu") && skill < 300)
                {
                        me->improve_skill("liandan-shu",query("int", me)/4+1);
                        tell_object(me, HIC "��������������ġ�������������ˣ�\n" NOR);
                }
        }
}