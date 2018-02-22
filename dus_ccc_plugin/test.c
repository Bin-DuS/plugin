#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
 
//动态链接库路径
//#define LIB_CACULATE_PATH "./libsource.so"
#define LIB_MUL "./libmul.so" // '*'
#define LIB_SUB "./libsub.so" // '-'
#define LIB_ADD "./libadd.so" // '+'
#define LIB_DIV "./libdiv.so" // '/'
 //函数指针
typedef int (*CAC_FUNC)(int, int);

int main(){
    void *handle;
    char *error;
	//char *lib_name = LIB_CACULATE_PATH
    CAC_FUNC cac_func = NULL;
	char lib_name[4][15] ={LIB_ADD,LIB_SUB,LIB_MUL,LIB_DIV};
	int a,b;
	char c;
	char opt[4][4]={"add","sub","mul","div"}; 
	int opt_flag;
	int exit_flag = 1;
	do{
		scanf("%d%c%d",&a,&c,&b);
		switch(c){
			case '+':
				//char *lib_name = LIB_ADD;
				//打开动态链接库
				//opt = "add";
				opt_flag = 0;
				handle = dlopen(lib_name[opt_flag], RTLD_LAZY);
				break;
			case '-':
				//char *lib_name = LIB_SUB;
				//opt = "sub";
				opt_flag = 1;
				handle = dlopen(lib_name[opt_flag], RTLD_LAZY);
				break;
			case '*':
				//char *lib_name = LIB_MUL;
				//opt = "mul";
				opt_flag = 2;
				handle = dlopen(lib_name[opt_flag], RTLD_LAZY);
				break;
			case '/':
				//char *lib_name = LIB_DIV;
				//opt = "div";
				opt_flag = 3;
				handle = dlopen(lib_name[opt_flag], RTLD_LAZY);
				break;
			default:
				printf("exit\n");
				exit_flag = 0;
			break;
		}
		if (!handle) {
			//fprintf(stderr, "%s\n", dlerror());
			printf("load %s error!\n",lib_name[opt_flag]);
			//exit(EXIT_FAILURE);
			continue;
		}
		//清除之前存在的错误
		dlerror(); 
		//获取函数
		*(void **) (&cac_func) = dlsym(handle, opt[opt_flag]);
		printf("%d %c %d = %d\n",a,c,b,(*cac_func)(a,b));
		//关闭动态链接库
		if (handle)
			dlclose(handle);
		//exit(EXIT_SUCCESS);
	}while(exit_flag != 0);
	return 0;
}

