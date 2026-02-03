// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Test the presence of RVA23 by reading the vector length and
 * the minimum positive normals provided by the Zfa extension.
 */

#include <stdio.h>

/**
 * get_vlenb() - get the vector length in bits
 *
 * Return:	vector length
 */
static unsigned int get_vlenb(void)
{
	unsigned int vlenb;

	__asm__ volatile (
		"csrr %0, vlenb"
		: "=r"(vlenb)
	);

	return 8 * vlenb;
}

/**
 * min_double() - load the minimum positive normal
 *
 * This tests the presence of the Zfa extension
 *
 * Return: minimum positive normal
 */
static double min_double() {
    double result = 1.;

    asm volatile (
        "fli.d %[out], min"
        : [out] "=f"(result)
    );

    return result;
}

/**
 * min_float() - load the minimum positive normal
 *
 * This tests the presence of the Zfa extension
 *
 * Return: minimum positive normal
 */
static float min_float() {
    float result = 1.f;

    asm volatile (
        "fli.s %[out], min"
        : [out] "=f"(result)
    );

    return result;
}

int main()
{
	printf("Welcome in a RISC-V world!\n\n");
	printf("The vector length is %u bits\n", get_vlenb());
	printf("fli.s min returned %e\n", min_float());
	printf("fli.d min returned %e\n", min_double());

	return 0;
}
