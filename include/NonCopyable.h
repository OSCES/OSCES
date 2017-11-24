#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

//  Private copy constructor and copy assignment ensure classes derived from
//  class NonCopyable cannot be copied.

class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {}

private: // emphasize the following members are private
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};

#endif // NONCOPYABLE_H
