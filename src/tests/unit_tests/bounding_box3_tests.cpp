// Copyright (c) 2016 Doyub Kim

#include <jet/bounding_box3.h>
#include <gtest/gtest.h>
#include <limits>

using namespace jet;

TEST(BoundingBox3, Constructors) {
    {
        BoundingBox3D box;

        static const double maxDouble = std::numeric_limits<double>::max();

        EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.x);
        EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.y);
        EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.z);

        EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.x);
        EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.y);
        EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.z);
    }

    {
        BoundingBox3D box(Vector3D(-2.0, 3.0, 5.0), Vector3D(4.0, -2.0, 1.0));

        EXPECT_DOUBLE_EQ(-2.0, box.lowerCorner.x);
        EXPECT_DOUBLE_EQ(-2.0, box.lowerCorner.y);
        EXPECT_DOUBLE_EQ(1.0, box.lowerCorner.z);

        EXPECT_DOUBLE_EQ(4.0, box.upperCorner.x);
        EXPECT_DOUBLE_EQ(3.0, box.upperCorner.y);
        EXPECT_DOUBLE_EQ(5.0, box.upperCorner.z);
    }

    {
        BoundingBox3D box(Vector3D(-2.0, 3.0, 5.0), Vector3D(4.0, -2.0, 1.0));
        BoundingBox3D box2(box);

        EXPECT_DOUBLE_EQ(-2.0, box2.lowerCorner.x);
        EXPECT_DOUBLE_EQ(-2.0, box2.lowerCorner.y);
        EXPECT_DOUBLE_EQ(1.0, box2.lowerCorner.z);

        EXPECT_DOUBLE_EQ(4.0, box2.upperCorner.x);
        EXPECT_DOUBLE_EQ(3.0, box2.upperCorner.y);
        EXPECT_DOUBLE_EQ(5.0, box2.upperCorner.z);
    }
}

TEST(BoundingBox3, Overlaps) {
    // x-axis is not overlapping
    {
        BoundingBox3D box1(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        BoundingBox3D box2(Vector3D(5.0, 1.0, 3.0), Vector3D(8.0, 2.0, 4.0));

        EXPECT_FALSE(box1.overlaps(box2));
    }

    // y-axis is not overlapping
    {
        BoundingBox3D box1(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        BoundingBox3D box2(Vector3D(3.0, 4.0, 3.0), Vector3D(8.0, 6.0, 4.0));

        EXPECT_FALSE(box1.overlaps(box2));
    }

    // z-axis is not overlapping
    {
        BoundingBox3D box1(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        BoundingBox3D box2(Vector3D(3.0, 1.0, 6.0), Vector3D(8.0, 2.0, 9.0));

        EXPECT_FALSE(box1.overlaps(box2));
    }

    // overlapping
    {
        BoundingBox3D box1(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        BoundingBox3D box2(Vector3D(3.0, 1.0, 3.0), Vector3D(8.0, 2.0, 7.0));

        EXPECT_TRUE(box1.overlaps(box2));
    }
}

TEST(BoundingBox3, Contains) {
    // Not containing (x-axis is out)
    {
        BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        Vector3D point(-3.0, 0.0, 4.0);

        EXPECT_FALSE(box.contains(point));
    }

    // Not containing (y-axis is out)
    {
        BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        Vector3D point(2.0, 3.5, 4.0);

        EXPECT_FALSE(box.contains(point));
    }

    // Not containing (z-axis is out)
    {
        BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        Vector3D point(2.0, 0.0, 0.0);

        EXPECT_FALSE(box.contains(point));
    }

    // Containing
    {
        BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        Vector3D point(2.0, 0.0, 4.0);

        EXPECT_TRUE(box.contains(point));
    }
}

TEST(BoundingBox3, MidPoint) {
    BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
    Vector3D midPoint = box.midPoint();

    EXPECT_DOUBLE_EQ(1.0, midPoint.x);
    EXPECT_DOUBLE_EQ(0.5, midPoint.y);
    EXPECT_DOUBLE_EQ(3.0, midPoint.z);
}

TEST(BoundingBox3, DiagonalLength) {
    BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
    double diagLen = box.diagonalLength();

    EXPECT_DOUBLE_EQ(std::sqrt(6.0*6.0 + 5.0*5.0 + 4.0*4.0), diagLen);
}

TEST(BoundingBox3, DiagonalLengthSquared) {
    BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
    double diagLenSqr = box.diagonalLengthSquared();

    EXPECT_DOUBLE_EQ(6.0*6.0 + 5.0*5.0 + 4.0*4.0, diagLenSqr);
}

TEST(BoundingBox3, Reset) {
    BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
    box.reset();

    static const double maxDouble = std::numeric_limits<double>::max();

    EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.x);
    EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.y);
    EXPECT_DOUBLE_EQ(maxDouble, box.lowerCorner.z);

    EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.x);
    EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.y);
    EXPECT_DOUBLE_EQ(-maxDouble, box.upperCorner.z);
}

TEST(BoundingBox3, Merge) {
    // Merge with point
    {
        BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        Vector3D point(5.0, 1.0, -1.0);

        box.merge(point);

        EXPECT_DOUBLE_EQ(-2.0, box.lowerCorner.x);
        EXPECT_DOUBLE_EQ(-2.0, box.lowerCorner.y);
        EXPECT_DOUBLE_EQ(-1.0, box.lowerCorner.z);

        EXPECT_DOUBLE_EQ(5.0, box.upperCorner.x);
        EXPECT_DOUBLE_EQ(3.0, box.upperCorner.y);
        EXPECT_DOUBLE_EQ(5.0, box.upperCorner.z);
    }

    // Merge with other box
    {
        BoundingBox3D box1(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
        BoundingBox3D box2(Vector3D(3.0, 1.0, 3.0), Vector3D(8.0, 2.0, 7.0));

        box1.merge(box2);

        EXPECT_DOUBLE_EQ(-2.0, box1.lowerCorner.x);
        EXPECT_DOUBLE_EQ(-2.0, box1.lowerCorner.y);
        EXPECT_DOUBLE_EQ(1.0, box1.lowerCorner.z);

        EXPECT_DOUBLE_EQ(8.0, box1.upperCorner.x);
        EXPECT_DOUBLE_EQ(3.0, box1.upperCorner.y);
        EXPECT_DOUBLE_EQ(7.0, box1.upperCorner.z);
    }
}

TEST(BoundingBox3, Expand) {
    BoundingBox3D box(Vector3D(-2.0, -2.0, 1.0), Vector3D(4.0, 3.0, 5.0));
    box.expand(3.0);

    EXPECT_DOUBLE_EQ(-5.0, box.lowerCorner.x);
    EXPECT_DOUBLE_EQ(-5.0, box.lowerCorner.y);
    EXPECT_DOUBLE_EQ(-2.0, box.lowerCorner.z);

    EXPECT_DOUBLE_EQ(7.0, box.upperCorner.x);
    EXPECT_DOUBLE_EQ(6.0, box.upperCorner.y);
    EXPECT_DOUBLE_EQ(8.0, box.upperCorner.z);
}