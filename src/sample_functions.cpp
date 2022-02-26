#include <ros/ros.h>
#include <std_msgs/Header.h>

void ifSample(void) {
    int a = 1;      // 整数型の変数
    float b = 1.2f; // 浮動小数点数の変数（doubleは4バイト）
    double c = 2.2; // 浮動小数点数の変数（doubleは8バイト）

    // 変数の表示．
    // intは%d，floatは%f，doubleは%lfで表示，\nは改行の意味です．
    printf("a = %d, b = %f, c = %lf\n", a, b, c);

    // ifとelseで真か偽か判断できます．
    if (a == 1) {
        printf("a is 1\n");
    } else {
        printf("a is not 1\n");
    }

    // 条件は複数つけることも可能です（&&で「どちらも」の意味）．
    if (b > 1.0f && c > 2.0) {
        printf("b is larger than 1 and c is larger than 2\n");
    }

    // 条件は複数つけることも可能です（||で「どちらか」の意味）．
    if (b > 2.0f || c > 2.0) {
        printf("b or c is larger than 2\n");
    // else ifで更に条件をつけることもできます．
    } else if (b > 3.0f || c > 3.0) {
        printf("b or c is larger than 3\n");
    }
    printf("\n");
}

void forSample(void) {
    // 0から9まで繰り返します（i < 10なので10は含まれません）．
    int sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += i;
    }
    printf("sum = %d\n", sum);

    // 5から10まで繰り返します（i <= 10なので10も含まれます）．
    sum = 0;
    for (int i = 5; i <= 10; ++i) {
        sum += i;
    }
    printf("sum = %d\n", sum);

    // 0から10まで2つ飛ばしで繰り返します．
    sum = 0;
    for (int i = 0; i <= 10; i += 2) {
        sum += i;
    }
    printf("sum = %d\n", sum);
    printf("\n");
}

void whileSample(void) {
    // 条件が真（正しい）の間無限にループします．
    int i = 0;
    while (i < 5) {
        printf("i = %d\n", i);
        i++;
    }

    // 途中でbreakをすると1つ前のループから抜け出します（forでも同じことができる）．
    i = 0;
    while (i < 10e50) {
        printf("i = %d\n", i);
        i++;
        if (i == 5) {
            printf("leave from the while loop since i = 5\n");
            break;
        }
    }
    printf("\n");
}

void pointerSample(int *a) {
    *a = 10;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "sample_functions");
    ros::NodeHandle nh("~");

    // 関数を呼び出します．
    // それぞれの関数の中身は上を参照してください．
    ifSample();
    forSample();
    whileSample();

    // ポインタを使った値のやり取りのサンプルです．
    // 関数からのreturn以外でも値をもらうことができます．
    int a;
    pointerSample(&a);
    printf("a = %d\n", a);
    printf("\n");

    return 0;
}