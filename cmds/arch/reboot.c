// reboot.c
// created by doing

#include <net/daemons.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

#ifndef STORAGE_D
#define STORAGE_D "/adm/daemons/storaged.c"
#endif

// ������ʱ��
int start_reboot = 0;
int last_notice = 0;

int is_rebooting() { return start_reboot != 0; }

protected void reboot_mud();

int main(object me, string arg)
{
        string str;
        int n;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
        {
                write("ָ���ʽ: shutdown [-f] | soon | after <n>\n");
                return 1;
        }

        str = me->name(1) + "(" + query("id", me) + ")";
        if (arg == "-f")
        {
                if (! find_object(SECURITY_D) ||
                    ! find_object(SIMUL_EFUN_OB) ||
                    ! find_object(MASTER_OB))
                        shutdown(0);

                if (! is_root(me))
                {
                        write("��û��Ȩ��ǿ��ֹͣ" + LOCAL_MUD_NAME() + "��\n");
                        return 1;
                }

                message_system(str + "ǿ��������" + LOCAL_MUD_NAME() + "��");
                shutdown(0);
                return 1;
        }

        if (wiz_level(me) < 4)
        {
                write("��û��Ȩ����������" + LOCAL_MUD_NAME() + "��\n");
                return 1;
        }

        if (sscanf(arg, "after %d", n) != 1)
        {
                if (arg != "soon")
                {
                        if (arg != "cancel")
                        {
                                write("����������鿴������\n");
                                return 1;
                        }

                        if (start_reboot)
                        {
                                start_reboot = 0;
                                set_heart_beat(0);
                                message_system(str + "ȡ������������Ϸ�������С�");
                                write("Ok.\n");
                                return 1;
                        }

                        write("����MUD�������������С�\n");
                        return 1;
                }
                message_system(str + "����������" + LOCAL_MUD_NAME() + "��");
                reboot_mud();
        }

        if (n < 1)
        {
                write("û����ô�̵�ʱ�䣬�㲻��ѡ�� soon ����������\n");
                return 1;
        }

        if (n > 10)
        {
                write("��ô�ã��㻹�ǵ�һ����������ɡ�\n");
                return 1;
        }

        start_reboot = time() + n * 60;
        last_notice = time();
        set_heart_beat(1);
        message_system(str + "������" + chinese_number(n) +
                       "�����Ժ���������" + LOCAL_MUD_NAME() + "��");
        return 1;
}

protected void heart_beat()
{
        int t;
        int n;
        string str;

        if (! start_reboot) return;

        n = start_reboot - time();
        if (n < 1)
        {
                reboot_mud();
                return;
        }

        if (n >= 60) str = chinese_number(n / 60) + "����"; else
                     str = "";
        if (n % 60) str += chinese_number(n % 60) + "��";

        t = time() - last_notice;
        if ((n >= 60 && t >= 60) || (n < 60 && n >= 10 && t >= 10) || n < 10)
        {
                message_system(LOCAL_MUD_NAME() + "����" +
                               str + "�Ժ�������������ץ��ʱ�䴦��������");
                last_notice = time();
        }
}

protected void reboot_mud()
{
        object *user, link_ob;
        int i;

        message_system("��Ϸ�������������Ժ�һ������ login ��\n");

        // �������е��ػ����̵�����
        reset_eval_cost();
        if (find_object(INTERMUD2_D))INTERMUD2_D->mud_shutdown();
        if (find_object(NAME_D))     NAME_D->mud_shutdown();
        if (find_object(CLOSE_D))    CLOSE_D->mud_shutdown();
        if (find_object(DBASE_D))    DBASE_D->mud_shutdown();
        if (find_object(SKILLS_D))   SKILLS_D->mud_shutdown();
        if (find_object(STORAGE_D))  STORAGE_D->mud_shutdown();
        user = users();
        for (i = 0; i < sizeof(user); i++)
        {
                reset_eval_cost();
                if (! environment(user[i])) continue;
                delete("quest_dg", user[i]);
                delete("quest_kh", user[i]);
                delete("quest_hs", user[i]);
                delete("quest_sn", user[i]);
                delete("quest", user[i]);
                user[i]->save();
                link_ob=query_temp("link_ob", user[i]);
                if (objectp(link_ob)) link_ob->save();
        }

        shutdown(0);
}

int help (object me)
{
        write(@HELP
ָ���ʽ: shutdown [-f] | soon | after <n> | cancel

��������Ϸ��������� -f ��������ϵͳǿ�����������������κ�
���ȣ����ǹ�ϵͳ����ʱʹ�õġ����ʹ���˲���soon����ϵͳ����
��������������ʹ�� after n ��ϵͳ���� n �����Ժ�����������

ʹ���� -f ������ soon �� after ��Ч��

���ʹ���� after ����������ʹ�� cancel ������ֹ�����Ĺ��̡�

HELP );
        return 1;
}