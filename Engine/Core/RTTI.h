#ifndef __RTTI_H__
#define __RTTI_H__

#include "Core.h"

class ENGINE_API RTTI
{
public:
    virtual const size_t& TypeIdInstance() const = 0;

    virtual bool Is(const size_t id) const
    {
        return false;
    }

    template<typename T>
    T* As()
    {
        if (Is(T::TypeIdClass()))
        {
            return (T*)this;
        }

        return nullptr;
    }

    template<typename T>
    const T* As() const
    {
        if (Is(T::TypeIdClass()))
        {
            return (T*)this;
        }

        return nullptr;
    }
};

#define RTTI_DECLARATIONS(Type, ParentType)                                          \
public:                                                                              \
    using super = ParentType;                                                        \
    virtual const size_t& TypeIdInstance() const override { return Type::TypeIdClass(); }     \
    static const size_t TypeIdClass()                                                \
    {                                                                                \
        static int runTimeTypeId = 0;                                                \
        return reinterpret_cast<size_t>(&runTimeTypeId);                             \
    }                                                                                \
    virtual bool Is(const size_t id) const override                                          \
    {                                                                                \
        if (id == TypeIdClass())                                                     \
        {                                                                            \
            return true;                                                             \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            return ParentType::Is(id);                                               \
        }                                                                            \
    }


#endif
