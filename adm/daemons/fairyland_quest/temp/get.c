// get.c
// last updated by April 2001.09.27     ��ֹ��˯������˯���˵Ķ���
// last updated by naihe 2002.09.25 
// ���ļ���ʹ��set("no_get","��Ϣ") ��ʽ�Զ���no_get��Ϣ��
// ʹ�� set("no_get","1") ��ʽ��ʹ��Ĭ����Ϣ����������ò�������
// ֮ǰ������趨Ϊ set("no_get",1) �ģ�Ҳ��ʹ��Ĭ����Ϣ��

#include <ansi.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string from, item,no_get_message;
        object obj, *inv, env, obj2;
        int i, amount, newa;

        if( !arg ) return notify_fail("��Ҫ����ʲô������\n");
        if( me->is_busy() )
                return notify_fail("����һ��������û����ɣ�\n");

        // Check if a container is specified.
        if( sscanf(arg, "%s from %s", arg, from)==2 ) {
                env = present(from, me);
                if(!env) env = present(from, environment(me));
                if(!env) return notify_fail("���Ҳ��� " + from + " ����������\n");
                if(wizardp(me) && living(env) && (wiz_level(me) <= wiz_level(env))
                 && !query("ridable", env) && env->query_lord() != me )
                        return notify_fail("�����ʦ�ȼ�����ȶԷ��ߣ�����������\n");
        } 
        else env = environment(me);
        
        // ������˯������˯���˵Ķ���
        if (!wizardp(me) && living(env) && env->query_lord() != me)
                return notify_fail("���컯�յ������ٰ���\n");
        else if( !wizardp(me) && query("no_get_from", env) )
                return notify_fail("�������˿����أ�������˼��������ٰɣ�\n");

        // Check if a certain amount is specified.
        if(sscanf(arg, "%d %s", amount, item)==2) {
                if( !objectp(obj = present(item, env)) )
                        return notify_fail("����û������������\n");
                if( !obj->query_amount() )
                        return notify_fail( obj->name() + "���ܱ��ֿ����ߡ�\n");
                if( amount < 1 )
                        return notify_fail("�����ĸ���������һ����\n");
                if( amount > obj->query_amount() )
                        return notify_fail("����û����ô���" + obj->name() + "��\n");
                else if( amount == (int)obj->query_amount() ) {
                        return do_get(me, obj);
               }else {
                        newa = (int)obj->query_amount();
                        obj->set_amount( amount );
                        obj2 = new(base_name(obj));
                        do_get(me, obj);
                        obj2->set_amount(newa - amount);
                        obj2->move(env);                        // For containers.
                        // Counting precise amount costs more time.
                        if( me->is_fighting() ) me->start_busy(3);
                        return 1;
                }
        }

        // Check if we are makeing a quick get.
        if(arg=="all") {
                if( me->is_fighting() ) return notify_fail("�㻹��ս���У�ֻ��һ����һ����\n");
                if( !env->query_max_encumbrance() )     return notify_fail("�ǲ���������\n");

                inv = all_inventory(env);
                if( !sizeof(inv) )
                        return notify_fail("������û���κζ�����\n");

                for(i=0; i<sizeof(inv); i++) {
                        if( inv[i]->is_character() || query("no_get", inv[i]))continue;
                        do_get(me, inv[i]);
                }
                write("����ˡ�\n");
                return 1;
        }

        if( !objectp(obj = present(arg, env)) || living(obj) )
                return notify_fail("�㸽��û������������\n");

// �޸�һ�������������
        if( query("no_get", obj) )
    {
        no_get_message=query("no_get", obj);
        if(!stringp(no_get_message) || no_get_message=="1") return notify_fail("��������ò�������\n");
        else return notify_fail(no_get_message+"\n");
    }

        return do_get(me, obj);
}
       
int do_get(object me, object obj)
{
        object old_env, *enemy;
        int equipped;
        string amt,no_get_message;

        if( !obj ) return 0;
        old_env = environment(obj);

        if( obj->is_character() ) {
                if( living(obj) ) return 0;
                //      if( !userp(obj) && !obj->is_corpse() )
                //              return notify_fail("��ֻ�ܱ���������ҵ����塣\n");
                // If we try to save someone from combat, take the risk :P
        }
    else if( query("no_get", obj) )
    {
        no_get_message=query("no_get", obj);
        if(!stringp(no_get_message) || no_get_message=="1") return notify_fail("��������ò�������\n");
        else return notify_fail(no_get_message+"\n");
    }

        if( query("equipped", obj))equipped=1;
        if( obj->query_amount()) amt = chinese_number(obj->query_amount());
        if( obj->move(me) ) {
                if( me->is_fighting() ) me->start_busy(1);
                if( obj->is_character() )
                        message_vision( "$N��$n�����������ڱ��ϡ�\n", me, obj );
                else
                        message_vision( sprintf("$N%s%s%s$n��\n", 
                                old_env==environment(me)? "����":
                                        (old_env->is_character() ?
                                                "��" + old_env->name() + "����" + (equipped? "����" : "�ѳ�"):
                                                "��" + old_env->name() + "���ó�"),
                                obj->query_amount()? amt : "һ", 
                                obj->query_amount()?query("base_unit", obj):query("unit", obj)),me,obj);
                return 1;
        }
        else return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : get <��Ʒ����> [from <������>]
 
���ָ��������������ϻ������ڵ�ĳ����Ʒ.
 
HELP
    );
    return 1;
}
 