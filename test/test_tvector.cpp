#include "../include/utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
  TVector<int> v(10);
  v[3] = 3;
  v[4] = -3;

  TVector<int> v1(v);

  TVector<int> rez(10);
  rez[3] = 3;
  rez[4] = -3;

  EXPECT_EQ(rez, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
  TVector<int> v(10);
  v[3] = 3;
  v[4] = -3;

  TVector<int> v1(v);

  v[3] = 4;

  EXPECT_NE(v1, v);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
  TVector<int> v(4);

  ASSERT_ANY_THROW(v[-4] = 6);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
  TVector<int> v(4);

  ASSERT_ANY_THROW(v[14] = 3);
}

TEST(TVector, can_assign_vector_to_itself)
{
  TVector<int> v(4);
  v[3] = 4;
  v[1] = 3;

  ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(4);
	v[3] = 4;
	v[1] = 3;
	// 0 3 0 4

	TVector<int> z(4);
	z[0] = -1;
	z[2] = -4;
	// -1 0 -4 0

	v = z;

	TVector<int> rez(4);
	rez[0] = -1;
	rez[2] = -4;
	// -1 0 -4 0

	EXPECT_EQ(rez, v);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(4);
	v[3] = 4;
	v[1] = 3;
	// 0 3 0 4

	TVector<int> z(6);
	z[0] = 234;
	z[2] = -54;
	z[5] = 1;
	// 234 0 -54 0 0 1

	v = z;

	EXPECT_EQ(6, v.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(4);
	v[3] = 4;
	v[1] = 3;
	// 0 3 0 4

	TVector<int> z(6);
	z[0] = 234;
	z[2] = -54;
	z[5] = 1;
	// 234 0 -54 0 0 1

	v = z;

	TVector<int> rez(6);
	rez[0] = 234;
	rez[2] = -54;
	rez[5] = 1;
	// 234 0 -54 0 0 1

	EXPECT_EQ(rez, v);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> r(6);
	r[0] = 234;
	r[2] = -54;
	r[5] = 1;
	// 234 0 -54 0 0 1

	TVector<int> y(6);
	y[0] = 234;
	y[2] = -54;
	y[5] = 1;
	// 234 0 -54 0 0 1

	EXPECT_EQ(1, y == r);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> rez(6);
	rez[0] = 234;
	rez[2] = -54;
	rez[5] = 1;
	// 234 0 -54 0 0 1

	EXPECT_EQ(1,rez == rez);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> r(6);
	// 0 0 ...

	TVector<int> y(70);
	// 0 0 ...

	EXPECT_EQ(1, y != r);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> x(6);
	x[0] = 10;
	x[2] = -10;
	x[5] = 1;
	// 10 0 -10 0 0 1
	x = x + 5;

	TVector<int> rez(6);
	rez[0] = 15;
	rez[1] = 5;
	rez[2] = -5;
	rez[3] = 5;
	rez[4] = 5;
	rez[5] = 6;
	// 15 5 -5 5 6 5

	EXPECT_EQ(rez, x);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> x(6);
	x[0] = 10;
	x[2] = -10;
	x[5] = 1;
	// 10 0 -10 0 1 0
	x = x - 5;

	TVector<int> rez(6);
	rez[0] = 5;
	rez[1] = -5;
	rez[2] = -15;
	rez[3] = -5;
	rez[4] = -5;
	rez[5] = -4;
	// 5 -5 -15 -5 -4 -5

	EXPECT_EQ(rez, x);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> x(3,0);
	x[0] = 0;
	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	x = x * 2;

	TVector<int> rez(3, 0);
	rez[0] = 0;
	rez[1] = 6;
	rez[2] = -6;
	// 0 6 -6

	EXPECT_EQ(rez, x);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> x(3, 1);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(3, 1);

	y[1] = 6;
	y[2] = -6;
	// 0 6 -6

	TVector<int> rez(3, 1);

	rez[1] = 9;
	rez[2] = -9;
	// 0 9 -9

	EXPECT_EQ(rez, x + y);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> x(3, 1);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(6, 3);

	y[4] = 56;
	y[5] = -67;
	// 0 0 0 0 56 -67

	ASSERT_ANY_THROW(x + y);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> x(3, 1);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(3, 1);

	y[1] = 6;
	y[2] = -6;
	// 0 6 -6

	TVector<int> rez(3, 1);

	rez[1] = -3;
	rez[2] = 3;
	// 0 -3 3

	EXPECT_EQ(rez, x - y);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> x(3, 1);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(6, 3);

	y[4] = 56;
	y[5] = -67;
	// 0 0 0 0 56 -67

	ASSERT_ANY_THROW(x - y);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> x(3);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(3);

	y[1] = 6;
	y[2] = -6;
	// 0 6 -6

	int rez = 36;
	// 3*6 + (-3)*(-6) = 18+18

	EXPECT_EQ(rez, x * y);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> x(3, 1);

	x[1] = 3;
	x[2] = -3;
	// 0 3 -3

	TVector<int> y(6, 3);

	y[4] = 56;
	y[5] = -67;
	// 0 0 0 0 56 -67

	ASSERT_ANY_THROW(x * y);
}

