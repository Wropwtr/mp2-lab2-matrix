#include "../include/utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	m[2][3] = 5;

	TMatrix<int> m1(m);

	TMatrix<int> rez(5);
	rez[2][3] = 5;

	EXPECT_EQ( rez, m1 );
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	m[2][3] = 5;

	TMatrix<int> m1(m);

	EXPECT_NE( &m, &m1 );
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);

	EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[2][2] = 228;

	EXPECT_EQ(228, m[2][2]);
}

TEST(TMatrix, throws_when_set_element_with_negative_row_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-2][2] = 228);
}

TEST(TMatrix, throws_when_set_element_with_negative_col_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[2][-2] = 228);
}

TEST(TMatrix, throws_when_set_element_with_too_large_row_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[62][2] = 228);
}

TEST(TMatrix, throws_when_set_element_with_too_large_col_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[2][62] = 228);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	m[2][2] = 228;

	m = m;

	TMatrix<int> rez(5);
	rez[2][2] = 228;

	EXPECT_EQ(m, rez);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> x(5);

	TMatrix<int> y(5);
	y[2][2] = -5;
	y[3][4] = 14;

	x = y;

	TMatrix<int> rez(5);
	rez[2][2] = -5;
	rez[3][4] = 14;

	EXPECT_EQ(rez, x);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> x(1);

	TMatrix<int> y(5);
	y[2][2] = -5;
	y[3][4] = 14;

	x = y;

	EXPECT_EQ(5, x.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> x(1);
	x[0][0] = 3;

	TMatrix<int> y(5);
	y[2][2] = -5;
	y[3][4] = 14;

	x = y;

	EXPECT_EQ(x, y);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> y(5);
	y[2][2] = -5;
	y[3][4] = 14;

	TMatrix<int> rez(5);
	rez[2][2] = -5;
	rez[3][4] = 14;

	EXPECT_EQ(1, rez == y);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> rez(5);
	rez[2][2] = -5;
	rez[3][4] = 14;

	EXPECT_EQ(1, rez == rez);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> a(3);
	/* 
	 * 1 0 1
	 * 0 3 -3
	 * 0 0 -10
	 */
	a[0][0] = 1;
	a[0][2] = 1;
	a[1][1] = 3;
	a[1][2] = -3;
	a[2][2] = -10;

	TMatrix<int> b(3);
	/*
	* 0 3 -1
	* 0 4 6
	* 0 0 10
	*/
	b[0][1] = 3;
	b[0][2] = -1;
	b[1][1] = 4;
	b[1][2] = 6;
	b[2][2] = 10;

	TMatrix<int> rez(3);
	/*
	* 1 3 0
	* 0 7 3
	* 0 0 0
	*/
	rez[0][0] = 1;
	rez[0][1] = 3;
	rez[1][1] = 7;
	rez[1][2] = 3;

	EXPECT_EQ(rez, a + b);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> a(2);
	a[1][1] = 3;

	TMatrix<int> b(4);
	b[2][3] = 4;

	ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, cant_add_null_reference)
{
	TMatrix<int> a(2);
	a[1][1] = 3;

	TMatrix<int> b = 0;

	ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> a(3);
	/*
	* 1 0 1
	* 0 3 -3
	* 0 0 -10
	*/
	a[0][0] = 1;
	a[0][2] = 1;
	a[1][1] = 3;
	a[1][2] = -3;
	a[2][2] = -10;

	TMatrix<int> b(3);
	/*
	* 0 3 -1
	* 0 4 6
	* 0 0 10
	*/
	b[0][1] = 3;
	b[0][2] = -1;
	b[1][1] = 4;
	b[1][2] = 6;
	b[2][2] = 10;

	TMatrix<int> rez(3);
	/*
	* 1 -3 2
	* 0 -1 -9
	* 0 0 -20
	*/
	rez[0][0] = 1;
	rez[0][1] = -3;
	rez[0][2] = 2;
	rez[1][1] = -1;
	rez[1][2] = -9;
	rez[2][2] = -20;

	EXPECT_EQ(rez, a - b);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> a(2);
	a[1][1] = 3;

	TMatrix<int> b(4);
	b[2][3] = 4;

	ASSERT_ANY_THROW(a - b);
}

