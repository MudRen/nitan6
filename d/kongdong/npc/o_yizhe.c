
inherit NPC;



void create()
{
        set_name("老年弈者", ({ "yi zhe","zhe" }) );
        set("gender", "男性" );
        set("age", 80);
        set("str", 46);
        set("cor", 40);
        set("cps", 40);
        set("per", 40);
        set("int", 40);

        set("attitude", "peaceful");

        set("force_factor", 10);
        set("max_gin", 500);
        set("max_kee", 500);
        set("max_sen", 500);
        set("eff_gin", 500);
        set("eff_kee", 500);
        set("eff_sen", 500);
        set("gin", 500);
        set("kee", 500);
        set("sen", 500);
        set("max_force", 3000);
        set("force", 3000);

        set("long",     "这是一个精神矍铄的老者，双目有神，闪烁着睿智的光芒。\n");


        set("combat_exp", 999999);
        set_wugong("force",100,100,0);
	set_wugong("dahong-quan", 100,100,1);
        set_wugong("kd-xinfa",100,100,0);
        set_wugong("ny-bufa",100,100,1);
	set_xiuwei("unarmed", 1000);
	set_xiuwei("dodge", 800);

        set("positive_score",100);
        setup();

        carry_object(__DIR__"obj/yifu2")->wear();
}

 
