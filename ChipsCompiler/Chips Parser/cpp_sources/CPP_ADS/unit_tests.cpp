#include <cstddef>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "./dimension_t.cpp"
#include "./dataflow_t.cpp"


/*
    *
    *   Dimension class tests
    *
    *
*/

TEST(DimensionTests, CreateDimension) {
    chips_ads::dimension_t d(4);
    EXPECT_EQ(d.get_cardinality(),4);
}

TEST(DimensionTests, CopyCreateDimension) {
    chips_ads::dimension_t d(4);
    chips_ads::dimension_t d2(d);
    EXPECT_EQ(d2.get_cardinality(),4);
}

TEST(DimensionTests, CreateDimensionFromArray) {
    chips_ads::dimension_t d({2,2});
    EXPECT_EQ(d.get_cardinality(),4);
}

TEST(DimensionTests, CreateDimensionFromArray2) {
    chips_ads::dimension_t d({2,3});
    EXPECT_EQ(d.get_cardinality(),6);
}

TEST(DimensionTests, CreateDimensionFromBadArray) {
    EXPECT_ANY_THROW(chips_ads::dimension_t d({0,3}));
}

TEST(DimensionTests, CreateDimensionFromBadArray2) {
    EXPECT_ANY_THROW(chips_ads::dimension_t d({1, 2, 3, 0}));
}

TEST(DimensionTests, CreateDimensionFromBadNumber) {
    EXPECT_ANY_THROW(chips_ads::dimension_t d(0));
}

TEST(DimensionTests, CreateBigDimension) {
    chips_ads::dimension_t d({1, 2, 3, 8, 20, 40});
    EXPECT_EQ(d.get_cardinality(),6*8*20*40);
}

TEST(DimensionTests, SameDimensions) {
    chips_ads::dimension_t d({1, 2, 3, 5, 6});
    chips_ads::dimension_t e({1, 2, 3, 5, 6});
    size_t depth = d.depth();
    EXPECT_EQ(depth,e.depth());
    for( size_t i = 0; i<depth; ++i){
        EXPECT_EQ(d.get_dimension()[i], e.get_dimension()[i]);
    }
}

TEST(DimensionTests, DifferentDimensions) {
    chips_ads::dimension_t d({6, 1, 2, 3, 5});
    chips_ads::dimension_t e({1, 2, 3, 5, 6});
    size_t depth = d.depth();
    EXPECT_EQ(depth,e.depth());
    for( size_t i = 0; i<depth; ++i){
        EXPECT_NE(d.get_dimension().at(i), e.get_dimension().at(i));
    }
}

TEST(DimensionTests, DimensionOtherAccessor) {
    chips_ads::dimension_t d({6, 1, 2, 3, 5});
    size_t depth = d.depth();
    EXPECT_EQ(6,d[0]);
    EXPECT_EQ(1,d[1]);
    EXPECT_EQ(2,d[2]);
    EXPECT_EQ(3,d[3]);
    EXPECT_EQ(5,d[4]);
}

TEST(DimensionTests, DimensionOtherAccessorBadUsage) {
    chips_ads::dimension_t d({6, 1, 2, 3, 5});
    size_t depth = d.depth();
    EXPECT_ANY_THROW(size_t a = d[5]);
}

TEST(DimensionTests, DifferentDimensionOtherAccessor) {
    chips_ads::dimension_t d({6, 1, 2, 3, 5});
    chips_ads::dimension_t e({1, 2, 3, 5, 6});
    size_t depth = d.depth();
    EXPECT_EQ(depth,e.depth());
    for( size_t i = 0; i<depth; ++i){
        EXPECT_NE(d[i], e[i]);
    }
}

TEST(DimensionTests, linearizeSimpleGood) {
    chips_ads::dimension_t d(2);
    EXPECT_EQ(d.linearize(1), 1);
}

TEST(DimensionTests, linearizeSimpleGood2) {
    chips_ads::dimension_t d(5);
    EXPECT_EQ(d.linearize(1), 1);
}

TEST(DimensionTests, linearizeSimpleGood3) {
    chips_ads::dimension_t d(5);
    EXPECT_EQ(d.linearize(4), 4);
}

TEST(DimensionTests, linearizeSimpleGood4) {
    chips_ads::dimension_t d(5);
    EXPECT_EQ(d.linearize(0), 0);
}

TEST(DimensionTests, linearizeSimpleBad) {
    chips_ads::dimension_t d(6);
    EXPECT_ANY_THROW(size_t s = d.linearize(6));
}

TEST(DimensionTests, linearizeSimpleBad2) {
    chips_ads::dimension_t d(1);
    EXPECT_ANY_THROW(size_t s = d.linearize(1));
}

TEST(DimensionTests, linearizeArrayBad) {
    chips_ads::dimension_t d({1,2,3});
    EXPECT_ANY_THROW(size_t s = d.linearize(1));
}

TEST(DimensionTests, linearizeArrayBad2) {
    chips_ads::dimension_t d({1,2,3});
    EXPECT_ANY_THROW(size_t s = d.linearize({1,4}));
}

TEST(DimensionTests, linearizeArrayGood) {
    EXPECT_EQ(chips_ads::dimension_t({3,2,5}).linearize({1,1,1}),1+3*1+3*2*1);
}

TEST(DimensionTests, linearizeArrayGood2) {
    EXPECT_EQ(chips_ads::dimension_t({5,5,5}).linearize({0,1,2}),0+5*1+25*2);
}

TEST(DimensionTests, equality) {
    EXPECT_TRUE(chips_ads::dimension_t({5,5,5})==chips_ads::dimension_t({5,5,5}));
}

TEST(DimensionTests, equality2) {
    EXPECT_TRUE(chips_ads::dimension_t({1,2,3})==chips_ads::dimension_t({1,2,3}));
}
TEST(DimensionTests, equality3) {
    EXPECT_TRUE(chips_ads::dimension_t(5)==chips_ads::dimension_t(5));
}

TEST(DimensionTests, equality4) {
    EXPECT_TRUE(chips_ads::dimension_t(std::vector<size_t>({5}))==chips_ads::dimension_t(5));
}

TEST(DimensionTests, equality5) {
    EXPECT_TRUE(chips_ads::dimension_t(5)==(size_t)5);
}

TEST(DimensionTests, equality6) {
    EXPECT_TRUE(chips_ads::dimension_t(5)==std::vector<size_t>({5}));
}

TEST(DimensionTests, inequality) {
    EXPECT_FALSE(chips_ads::dimension_t({5,5,5})==chips_ads::dimension_t({5,5,4}));
}

TEST(DimensionTests, inequality2) {
    EXPECT_FALSE(chips_ads::dimension_t({1,2,3})==chips_ads::dimension_t({1,2}));
}
TEST(DimensionTests, inequality3) {
    EXPECT_FALSE(chips_ads::dimension_t(5)==chips_ads::dimension_t(4));
}

TEST(DimensionTests, inequality4) {
    EXPECT_FALSE(chips_ads::dimension_t(std::vector<size_t>({6}))==chips_ads::dimension_t(5));
}

TEST(DimensionTests, inequality5) {
    EXPECT_FALSE(chips_ads::dimension_t(5)==4);
}

TEST(DimensionTests, inequality6) {
    EXPECT_FALSE(chips_ads::dimension_t(5)==std::vector<size_t>({5, 3}));
}


/*
    *
    *   Dataflow class tests
    *
    *
*/

TEST(DataflowTests, Create1INT_DF){
    chips_ads::dataflow_t my_df_var(INT_DF);
    EXPECT_FALSE(my_df_var.in_use());
}

TEST(DataflowTests, Assign1INT_DF){
    chips_ads::dataflow_t my_df_var(INT_DF);
    EXPECT_FALSE(my_df_var.in_use());
    my_df_var.set_value(-4);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, Assign1FLOAT_DF){
    chips_ads::dataflow_t my_df_var(FLOAT_DF);
    EXPECT_FALSE(my_df_var.in_use());
    my_df_var.set_value(4.1);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, Assign1BOOL_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF);
    EXPECT_FALSE(my_df_var.in_use());
    my_df_var.set_value(true);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, Assign1INT_DFWrongAssign){
    chips_ads::dataflow_t my_df_var(INT_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(true));
}

TEST(DataflowTests, Assign1FLOAT_DFWrongAssign){
    chips_ads::dataflow_t my_df_var(FLOAT_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(4));
}

TEST(DataflowTests, Assign1BOOL_DFWrongAssign){
    chips_ads::dataflow_t my_df_var(BOOL_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(5.3));
}

TEST(DataflowTests, Assign1INT_DFWrongAssign2){
    chips_ads::dataflow_t my_df_var(INT_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(-4.6));
}

TEST(DataflowTests, Assign1FLOAT_DFWrongAssign2){
    chips_ads::dataflow_t my_df_var(FLOAT_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(false));
}

TEST(DataflowTests, Assign1BOOL_DFWrongAssign2){
    chips_ads::dataflow_t my_df_var(BOOL_DF);
    EXPECT_ANY_THROW(my_df_var.set_value(5));
}


TEST(DataflowTests, ReAssign1INT_DF){
    chips_ads::dataflow_t my_df_var(INT_DF);
    chips_ads::dataflow_t my_df_var2(INT_DF);
    my_df_var.set_value(-4);
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, ReAssign1BOOL_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF);
    chips_ads::dataflow_t my_df_var2(BOOL_DF);
    my_df_var.set_value(false);
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());

}

TEST(DataflowTests, ReAssign1FLOAT_DF){
    chips_ads::dataflow_t my_df_var(FLOAT_DF);
    chips_ads::dataflow_t my_df_var2(FLOAT_DF);
    my_df_var.set_value(5.3);
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, CreateManyBOOL_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF, std::vector<size_t>({5}));
}

TEST(DataflowTests, ReAssignManyBOOL_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF, std::vector<size_t>({2}));
    chips_ads::dataflow_t my_df_var2(BOOL_DF, std::vector<size_t>({2}));
    my_df_var.set_value(false, std::vector<size_t>({0}));
    my_df_var.set_value(false, std::vector<size_t>({1}));
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, ReAssignManyINT_DF){
    chips_ads::dimension_t dim(2);
    chips_ads::dataflow_t my_df_var(INT_DF, dim);
    chips_ads::dataflow_t my_df_var2(INT_DF, dim);
    my_df_var.set_value(5, std::vector<size_t>({0}));
    my_df_var.set_value(-6, std::vector<size_t>({1}));
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());

}
TEST(DataflowTests, ReAssignManyFLOAT_DF){
    chips_ads::dataflow_t my_df_var(FLOAT_DF, std::vector<size_t>({2}));
    chips_ads::dataflow_t my_df_var2(FLOAT_DF, std::vector<size_t>({2}));
    my_df_var.set_value(5.4, std::vector<size_t>({0}));
    my_df_var.set_value(-10.4, std::vector<size_t>({1}));
    EXPECT_FALSE(my_df_var2.in_use());
    my_df_var2.set_value(my_df_var);
    EXPECT_TRUE(my_df_var.in_use());
}

TEST(DataflowTests, ReAssignManyBOOL_DF2ManyINT_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF, std::vector<size_t>({2}));
    chips_ads::dataflow_t my_df_var2(INT_DF, std::vector<size_t>({2}));
    my_df_var.set_value(false, std::vector<size_t>({0}));
    my_df_var.set_value(false, std::vector<size_t>({1}));
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}

TEST(DataflowTests, ReAssignManyINT_DF2ManyINT_DFOfDiffSize){
    chips_ads::dataflow_t my_df_var(INT_DF, std::vector<size_t>({2,3,4,2}));
    chips_ads::dataflow_t my_df_var2(INT_DF, std::vector<size_t>({2,3,4,3}));
    my_df_var = 5;
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}


TEST(DataflowTests, ReAssignManyINT_DF2ManyINT_DFOfDiffDepth){
    chips_ads::dataflow_t my_df_var(INT_DF, std::vector<size_t>({2,3,4}));
    chips_ads::dataflow_t my_df_var2(INT_DF, std::vector<size_t>({2,3,4,3}));
    my_df_var = 5;
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}

TEST(DataflowTests, ReAssignManyBOOL_DF2ManyFLOAT_DF){
    chips_ads::dataflow_t my_df_var(BOOL_DF, std::vector<size_t>({2}));
    chips_ads::dataflow_t my_df_var2(FLOAT_DF, std::vector<size_t>({2}));
    my_df_var.set_value(false, std::vector<size_t>({0}));
    my_df_var.set_value(false, std::vector<size_t>({1}));
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}

TEST(DataflowTests, ReAssignManyFLOAT_DF2ManyFLOAT_DFOfDiffSize){
    chips_ads::dataflow_t my_df_var(FLOAT_DF, std::vector<size_t>({2,3,4,2}));
    chips_ads::dataflow_t my_df_var2(FLOAT_DF, std::vector<size_t>({2,3,4,3}));
    my_df_var = 5.4563;
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}


TEST(DataflowTests, ReAssignManyFLOAT_DF2ManyFLOAT_DFOfDiffDepth){
    chips_ads::dataflow_t my_df_var(FLOAT_DF, std::vector<size_t>({2,3,4}));
    chips_ads::dataflow_t my_df_var2(FLOAT_DF, std::vector<size_t>({2,3,4,3}));
    my_df_var = 5.0;
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}

TEST(DataflowTests, ReAssignManyFLOAT_DF2ManyFLOAT_DFOfDiffSize2){
    chips_ads::dataflow_t my_df_var(FLOAT_DF,4);
    chips_ads::dataflow_t my_df_var2(FLOAT_DF,3);
    my_df_var = -4.3;
    EXPECT_TRUE(my_df_var.in_use());
    EXPECT_FALSE(my_df_var2.in_use());
    EXPECT_ANY_THROW(my_df_var2.set_value(my_df_var));
}




int main(int argc, char **argv) {
    std::cout<<"Starting to run the tests...";
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}