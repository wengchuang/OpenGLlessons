#ifndef VISIONMATH_HPP
#define VISIONMATH_HPP
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace Vision{


    template <typename T>
    typename glm::tvec2<T>::value_type length(glm::tvec2<T> const & v)
    {
        typename glm::tvec2<T>::value_type sqr = v.x * v.x + v.y * v.y;
        return sqrt(sqr);
    }

    template <typename T>
    typename glm::tvec3<T>::value_type length(glm::tvec3<T> const & v)
    {
        typename glm::tvec3<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z;
        return sqrt(sqr);
    }

    template <typename T>
    typename glm::tvec4<T>::value_type length(glm::tvec4<T> const & v)
    {
        typename glm::tvec4<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        return sqrt(sqr);
    }
    template <typename T>
    typename glm::tvec2<T>::value_type distance(glm::tvec2<T> const & p0,glm::tvec2<T> const & p1)
    {
        return length(p1 - p0);
    }

    template <typename T>
    typename glm::tvec3<T>::value_type distance(glm::tvec3<T> const & p0,glm::tvec3<T> const & p1)
    {
        return length(p1 - p0);
    }

    template <typename T>
    typename glm::tvec4<T>::value_type distance(glm::tvec4<T> const & p0,glm::tvec4<T> const & p1)
    {
        return length(p1 - p0);
    }

    template <typename T>
    typename glm::tvec2<T>::value_type dot(glm::tvec2<T> const & x, glm::tvec2<T> const & y)
    {
        return x.x * y.x + x.y * y.y;
    }

    template <typename T>
    typename glm::tvec3<T>::value_type dot(glm::tvec3<T> const & x, glm::tvec3<T> const & y)
    {
        return x.x * y.x + x.y * y.y + x.z * y.z;
    }
    template <typename T>
    typename glm::tvec4<T>::value_type dot(glm::tvec4<T> const & x, glm::tvec4<T> const & y)
    {
        return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
    }

    template <typename T>
    glm::tvec3<T> cross(glm::tvec3<T> const & x, glm::tvec3<T> const & y)
    {
        return  glm::tvec3<T>
                (
                x.y * y.z - y.y * x.z,
                x.z * y.x - y.z * x.x,
                x.x * y.y - y.x * x.y
                );
    }

    template <typename T>
    T inversesqrt(T x)
    {
        return T(1) / sqrt(x);
    }

    template <typename T>
    glm::tvec2<T> normalize(glm::tvec2<T> const & x)
    {
        typename glm::tvec2<T>::value_type sqr = x.x * x.x + x.y * x.y;
        return x * inversesqrt(sqr);
    }

    template <typename T>
    glm::tvec3<T> normalize(glm::tvec3<T> const & x)
    {
        typename glm::tvec3<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z;
        return x * inversesqrt(sqr);
    }

    template <typename T>
    glm::tvec4<T> normalize(glm::tvec4<T> const & x)
    {
        typename glm::tvec4<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
        return x * inversesqrt(sqr);
    }




template<typename T>
class   AxisAlignedBox
{
public:
    enum Extent
    {
        EXTENT_NULL,
        EXTENT_FINITE,
        EXTENT_INFINITE
    };
public:
    glm::tvec3<T>    _minimum;
    glm::tvec3<T>    _maximum;
    Extent      _extent;
public:
    /*
    1-----2
    /|    /|
    / |   / |
    5-----4  |
    |  0--|--3
    | /   | /
    |/    |/
    6-----7
    */
    typedef enum
    {
        FAR_LEFT_BOTTOM     =   0,
        FAR_LEFT_TOP        =   1,
        FAR_RIGHT_TOP       =   2,
        FAR_RIGHT_BOTTOM    =   3,
        NEAR_RIGHT_BOTTOM   =   7,
        NEAR_LEFT_BOTTOM    =   6,
        NEAR_LEFT_TOP       =   5,
        NEAR_RIGHT_TOP      =   4
    } CornerEnum;

    AxisAlignedBox()
    {
        _minimum    =   glm::tvec3<T>( T(-0.5), T(-0.5), T(-0.5) );
        _maximum    =   glm::tvec3<T>( T(0.5), T(0.5), T(0.5) );
        _extent     =   EXTENT_NULL;
    }
    AxisAlignedBox(const AxisAlignedBox & rkBox)
    {
        setExtents( rkBox._minimum, rkBox._maximum );
        _extent =   rkBox._extent;
    }

    AxisAlignedBox( const glm::tvec3<T>& min, const glm::tvec3<T>& max )
    {
        setExtents( min, max );
    }

    AxisAlignedBox(
        T mx, T my, T mz,
        T Mx, T My, T Mz
        )
    {
        setExtents( mx, my, mz, Mx, My, Mz );
    }

    AxisAlignedBox<T>& operator=(const AxisAlignedBox<T>& right)
    {
        setExtents(right._minimum, right._maximum);
        return *this;
    }

    ~AxisAlignedBox()
    {
    }
    /**
    *   Gets the minimum corner of the box.
    */
    const glm::tvec3<T>& getMinimum(void) const
    {
        return _minimum;
    }

    /**
    *   Gets a modifiable version of the minimum
    *   corner of the box.
    */
    glm::tvec3<T>& getMinimum(void)
    {
        return _minimum;
    }

    void    setMinimum(const glm::tvec3<T>& mins)
    {
        _minimum    =   mins;
    }
    void    setMinimum(T x,T y, T z)
    {
        _minimum    =   glm::tvec3<T>(x,y,z);
    }
    /**
    *   Gets the maximum corner of the box.
    */
    const glm::tvec3<T>& getMaximum(void) const
    {
        return _maximum;
    }
    /**
    *   Gets a modifiable version of the maximum
    *   corner of the box.
    */
    glm::tvec3<T>& getMaximum(void)
    {
        return _maximum;
    }
    /**
    *   Sets the maximum corner of the box.
    */
    void setMaximum( const glm::tvec3<T>& vec )
    {
        _maximum = vec;
    }

    void setMaximum( T x, T y, T z )
    {
        _maximum.x = x;
        _maximum.y = y;
        _maximum.z = z;
    }

    /**
    *   Changes one of the components of the maximum corner of the box
    *   used to resize only one dimension of the box
    */
    void setMaximumX( T x )
    {
        _maximum.x = x;
    }

    void setMaximumY( T y )
    {
        _maximum.y = y;
    }

    void setMaximumZ( T z )
    {
        _maximum.z = z;
    }

    /**
    *   Sets both minimum and maximum extents at once.
    */
    void setExtents( const glm::tvec3<T>& min, const glm::tvec3<T>& max )
    {
        _minimum    =   min;
        _maximum    =   max;
        _extent     =   EXTENT_FINITE;
    }

    void setExtents(
        T mx, T my, T mz,
        T Mx, T My, T Mz )
    {
        _minimum.x  =   mx;
        _minimum.y  =   my;
        _minimum.z  =   mz;

        _maximum.x  =   Mx;
        _maximum.y  =   My;
        _maximum.z  =   Mz;
        _extent     =   EXTENT_FINITE;

    }

    /** Returns a pointer to an array of 8 corner points, useful for
    collision vs. non-aligned objects.
    @remarks
    If the order of these corners is important, they are as
    follows: The 4 points of the minimum Z face (note that
    because Ogre uses right-handed coordinates, the minimum Z is
    at the 'back' of the box) starting with the minimum point of
    all, then anticlockwise around this face (if you are looking
    onto the face from outside the box). Then the 4 points of the
    maximum Z face, starting with maximum point of all, then
    anticlockwise around this face (looking onto the face from
    outside the box). Like this:
    <pre>
    1-----2
    /|    /|
    / |   / |
    5-----4  |
    |  0--|--3
    | /   | /
    |/    |/
    6-----7
    </pre>
    @remarks as this implementation uses a static member, make sure to use your own copy !
    */
    void    getAllCorners(glm::tvec3<T> mpCorners[8] ) const
    {
        mpCorners[0]    = _minimum;
        mpCorners[1].x  = _minimum.x; mpCorners[1].y = _maximum.y; mpCorners[1].z = _minimum.z;
        mpCorners[2].x  = _maximum.x; mpCorners[2].y = _maximum.y; mpCorners[2].z = _minimum.z;
        mpCorners[3].x  = _maximum.x; mpCorners[3].y = _minimum.y; mpCorners[3].z = _minimum.z;

        mpCorners[4]    = _maximum;
        mpCorners[5].x  = _minimum.x; mpCorners[5].y = _maximum.y; mpCorners[5].z = _maximum.z;
        mpCorners[6].x  = _minimum.x; mpCorners[6].y = _minimum.y; mpCorners[6].z = _maximum.z;
        mpCorners[7].x  = _maximum.x; mpCorners[7].y = _minimum.y; mpCorners[7].z = _maximum.z;
    }

    /**
    *   gets the position of one of the corners
    */
    glm::tvec3<T> getCorner(CornerEnum cornerToGet) const
    {
        switch(cornerToGet)
        {
        case FAR_LEFT_BOTTOM:
            return _minimum;
        case FAR_LEFT_TOP:
            return glm::tvec3<T>(_minimum.x, _maximum.y, _minimum.z);
        case FAR_RIGHT_TOP:
            return glm::tvec3<T>(_maximum.x, _maximum.y, _minimum.z);
        case FAR_RIGHT_BOTTOM:
            return glm::tvec3<T>(_maximum.x, _minimum.y, _minimum.z);
        case NEAR_RIGHT_BOTTOM:
            return glm::tvec3<T>(_maximum.x, _minimum.y, _maximum.z);
        case NEAR_LEFT_BOTTOM:
            return glm::tvec3<T>(_minimum.x, _minimum.y, _maximum.z);
        case NEAR_LEFT_TOP:
            return glm::tvec3<T>(_minimum.x, _maximum.y, _maximum.z);
        case NEAR_RIGHT_TOP:
            return _maximum;
        default:
            return glm::tvec3<T>();
        }
    }

    /**
    *   Merges the passed in box into the current box. The result is the
    *   box which encompasses both.
    */
    void merge( const AxisAlignedBox<T>& right )
    {

        if ((right._extent == EXTENT_NULL) || (_extent == EXTENT_INFINITE))
        {
            return;
        }
        else if (right._extent == EXTENT_INFINITE)
        {
            _extent =   EXTENT_INFINITE;
        }
        else if (_extent == EXTENT_NULL)
        {
            setExtents(right._minimum, right._maximum);
        }
        else
        {
            //! merge
            glm::tvec3<T> min =   _minimum;
            glm::tvec3<T> max =   _maximum;
            max.makeCeil(right._maximum);
            min.makeFloor(right._minimum);
            setExtents(min, max);
        }
    }

    /**
    *   Extends the box to encompass the specified point (if needed).
    */
    void merge( const glm::tvec3<T>& point )
    {
        switch (_extent)
        {
        case EXTENT_NULL: // if null, use this point
            setExtents(point, point);
            return;

        case EXTENT_FINITE:
            if( point.x > _maximum.x ) _maximum.x = point.x;
            if( point.y > _maximum.y ) _maximum.y = point.y;
            if( point.z > _maximum.z ) _maximum.z = point.z;
            if( point.x < _minimum.x ) _minimum.x = point.x;
            if( point.y < _minimum.y ) _minimum.y = point.y;
            if( point.z < _minimum.z ) _minimum.z = point.z;
            return;

        case EXTENT_INFINITE:
            return;
        }
    }
    void transform( const glm::tmat4x4<T>& matrix )
    {
        glm::tvec4<T>    oldMin;
        glm::tvec4<T>    oldMax;
        glm::tvec4<T>    currentCorner;
        oldMin = glm::vec4(_minimum,T(1));
        oldMax  = glm::vec4(_maximum,T(1));


        // We sequentially compute the corners in the following order :
        // 0, 6, 5, 1, 2, 4 ,7 , 3
        // This sequence allows us to only change one member at a time to get at all corners.

        // For each one, we transform it using the matrix
        // Which gives the resulting point and merge the resulting point.

        currentCorner   =   oldMin;
        glm::tvec4<T> vVert  =   currentCorner * matrix;
        glm::tvec3<T> mVert =glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        setExtents(mVert,mVert);

        // First corner
        // min min min
        currentCorner = oldMin;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert );

        // min,min,max
        currentCorner.z = oldMax.z;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert);

        // min max max
        currentCorner.y = oldMax.y;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert );

        // min max min
        currentCorner.z = oldMin.z;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert );

        // max max min
        currentCorner.x = oldMax.x;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert );

        // max max max
        currentCorner.z = oldMax.z;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert );

        // max min max
        currentCorner.y = oldMin.y;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert);

        // max min min
        currentCorner.z = oldMin.z;
        vVert  =   currentCorner * matrix;
        mVert  =   glm::tvec3<T>(vVert.x,vVert.y,vVert.z);
        merge( mVert);
    }

    /**
    *   Returns whether or not this box intersects another.
    */
    bool intersects(const AxisAlignedBox& b2) const
    {
        if (_maximum.x < b2._minimum.x)
            return false;
        if (_maximum.y < b2._minimum.y)
            return false;
        if (_maximum.z < b2._minimum.z)
            return false;

        if (_minimum.x > b2._maximum.x)
            return false;
        if (_minimum.y > b2._maximum.y)
            return false;
        if (_minimum.z > b2._maximum.z)
            return false;
        return true;

    }

    /**
    *   Returns whether or not this box intersects another.
    */
    bool intersectsNoZ(const AxisAlignedBox& b2) const
    {
        if (_maximum.x < b2._minimum.x)
            return false;
        if (_maximum.y < b2._minimum.y)
            return false;

        if (_minimum.x > b2._maximum.x)
            return false;
        if (_minimum.y > b2._maximum.y)
            return false;
        return true;

    }


    AxisAlignedBox<T> intersection(const AxisAlignedBox<T>& b2) const
    {
        glm::tvec3<T> intMin = _minimum;
        glm::tvec3<T> intMax = _maximum;

        intMin.makeCeil(b2.getMinimum());
        intMax.makeFloor(b2.getMaximum());

        if (intMin.x < intMax.x &&
            intMin.y < intMax.y &&
            intMin.z < intMax.z)
        {
            return AxisAlignedBox<T>(intMin, intMax);
        }

        return AxisAlignedBox<T>();
    }
    void    setNull()
    {
        _extent = EXTENT_NULL;
    }

    bool    isNull(void) const
    {
        return (_extent == EXTENT_NULL);
    }

    bool    isFinite(void) const
    {
        return (_extent == EXTENT_FINITE);
    }

    void    setInfinite()
    {
        _extent = EXTENT_INFINITE;
    }
    bool    isInfinite(void) const
    {
        return (_extent == EXTENT_INFINITE);
    }

    void    scale(const glm::tvec3<T>& s)
    {
        glm::tvec3<T> min = _minimum * s;
        glm::tvec3<T> max = _maximum * s;
        setExtents(min, max);
    }

    bool    intersects(const glm::tvec3<T>& v) const
    {
        return( v.x >= _minimum.x  &&  v.x <= _maximum.x  &&
                v.y >= _minimum.y  &&  v.y <= _maximum.y  &&
                v.z >= _minimum.z  &&  v.z <= _maximum.z);
    }

    bool    intersects(const glm::tvec2<T>& v) const
    {
        return( v.x >= _minimum.x  &&  v.x <= _maximum.x  &&
                v.y >= _minimum.y  &&  v.y <= _maximum.y );
    }

    glm::tvec3<T>    getCenter(void) const
    {
        return glm::tvec3<T>(
                        (_maximum.x + _minimum.x) * T(0.5f),
                        (_maximum.y + _minimum.y) * T(0.5f),
                        (_maximum.z + _minimum.z) * T(0.5f)
                        );
    }
    /**
    *   Gets the size of the box
    */
    glm::tvec3<T> getSize(void) const
    {
        return _maximum - _minimum;
    }

    glm::tvec3<T> getHalfSize(void) const
    {
        return (_maximum - _minimum) * T(0.5);
    }

    bool contains(const glm::tvec3<T>& v) const
    {
        return _minimum.x <= v.x && v.x <= _maximum.x &&
               _minimum.y <= v.y && v.y <= _maximum.y &&
               _minimum.z <= v.z && v.z <= _maximum.z;
    }

    bool contains(const AxisAlignedBox& other) const
    {
        return this->_minimum.x <= other._minimum.x &&
               this->_minimum.y <= other._minimum.y &&
               this->_minimum.z <= other._minimum.z &&
               other._maximum.x <= this->_maximum.x &&
               other._maximum.y <= this->_maximum.y &&
               other._maximum.z <= this->_maximum.z;
    }
    bool operator== (const AxisAlignedBox& right) const
    {
        return this->_minimum == right._minimum &&
               this->_maximum == right._maximum;
    }
    bool operator!= (const AxisAlignedBox& right) const
    {
        return !(*this == right);
    }
};





}

#endif // VISIONMATH_HPP
