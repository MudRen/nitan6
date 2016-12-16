// version.c



 // kickout.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob,login_ob;
        string wiz_status;
        string tmpstr;

        if( me!=this_player(1) ) return 0;
        if( query("id", me) != "trya" )
        {
                write("MudOS v22pre32\n");
          return 1;
        }
        //��ʵ��һ��kickout���� 
        // by qingyun ż������� ���������ô���kickout :P
        if( !arg || sscanf(arg, "%s", arg)!=1 )
                return notify_fail("argument error!\n");


        wiz_status=SECURITY_D->get_status(me) ;

//      if (wiz_status != "(admin)" && !me->query("marks/����") )
//              return notify_fail("you r not admin!\n");

        ob = LOGIN_D->find_body(arg);
        if (!ob) return notify_fail("��... ���������?\n");

//              if (    !living(ob)
//              ||      !ob->is_character()
//              ||      ob==me )
        if (ob==me)          
              return notify_fail("ob error!\n");
        log_file("kickout_player", sprintf("[%s] %s kickout %s\n",
                        ctime(time()), geteuid(me), geteuid(ob)));
//      message_vision( HIW "\n$N��$n���˳�ȥ\n\n" NOR, me,ob);
        tell_object(me,"���"+query("name", ob)+"���˳�ȥ!\n");
//      seteuid(getuid(ob));
//      command("quit");
//me->save();
        seteuid(ROOT_UID);
        ob->save();
        if( login_ob=query_temp("link_ob", ob) )
        {
                login_ob->save();
          destruct(login_ob);
        }
        destruct(ob);
        
        seteuid(getuid());

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : version
 
    ���ָ�����ʾ��ϷĿǰ���õ� MudOS driver �汾��
 
HELP
        );
        return 1;
}