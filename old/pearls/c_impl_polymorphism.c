/* how to simulate C++'s polymorphism with C */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* declaration of virtual method */
typedef void (*Func1)(void);
typedef void (*Func2)(int);
typedef void (*Func3)(char *);

/* ------------------- Base Class begin ------------------*/
void func1_base(void)
{
	printf("func1_base(void) called\n");
}

void func2_base(int item)
{
	printf("func2_base(%d) called\n", item);
}

struct Vtbl_Base {
	Func1 f1;
	Func2 f2;
};
struct Vtbl_Base bvtbl = {&func1_base, &func2_base};

struct Base {
	void *vptr; /* pointer to VTABLE */
	int field_base;
};

void Base_Init(struct Base *base, int value)
{
	base->vptr = &bvtbl;
	base->field_base = value;
}

/* ------------------- Base Class end ------------------*/

/* ------------------- Derived Class begin ------------------*/
void func1_derived(void)
{
	printf("func1_derived(void) called\n");
}

void func3_derived(char *item)
{
	printf("func3_derived(%s) called\n", item);
}

struct Vtbl_Derived {
	struct Vtbl_Base vtbl_base;
	Func3 f3;
};
struct Vtbl_Derived dvtbl = {{&func1_derived, &func2_base}, &func3_derived};

struct Derived {
	struct Base base;
	int field_derived;
};

void Derived_Init(struct Derived *derived, int b, int d)
{
	Base_Init((struct Base *)derived, b);
	derived->base.vptr = &dvtbl;
	derived->field_derived = d;
}

/* ------------------- Derived Class end ------------------*/

void 
test_polymorphism(struct Base *obj)
{
	((struct Vtbl_Base *)(obj->vptr))->f1();
	((struct Vtbl_Base *)(obj->vptr))->f2(obj->field_base);
}

int
main(int argc, char **argv)
{
	struct Base base;
	Base_Init(&base, 128);
	test_polymorphism(&base);

	struct Derived derived;
	Derived_Init(&derived, 128, 256);
	test_polymorphism((struct Base *)&derived);

	((struct Vtbl_Derived *)(*(int *)&derived))->f3("polymorphism");
}
