template <class Return, class ... Args>
class delegate
{
public:
    delegate()
        : object_ptr(nullptr)
        , stub_ptr(nullptr)
		, stub_non_member_ptr(nullptr)
    {}

	// 멤버 함수를 등록할 때 사용
    template <class T, Return(T::* function)(Args ...)>
    static delegate from_method(T* object_ptr)
    {
        delegate d;
        d.object_ptr = object_ptr;
        d.stub_ptr = &method_stub<T, function>;
        return d;
    }

	// 일반 함수를 등록할 때 사용
	template <void (*function)(Args ...)>
	static delegate from_method()
	{
		delegate d;
		d.object_ptr = nullptr;
		d.stub_non_member_ptr = &method_stub<function>;
		return d;
	}

	Return operator()(Args ... args) const
    {
		if (nullptr == object_ptr)
			return (stub_non_member_ptr)(args ...);
		else
			return (stub_ptr)(object_ptr, args ...);
    }

private:

	// 함수 포인터를 가지고 있을 타입
	using stub_type = Return(void* object_ptr, Args ...);
	using stub_type_none_member = Return(Args ...);

    void* object_ptr;
    stub_type* stub_ptr;
	stub_type_none_member* stub_non_member_ptr;

    template <class T, Return(T::* function)(Args ...)>
    static Return method_stub(void* object_ptr, Args ... args)
    {
        T* p = static_cast<T*>(object_ptr);
        return (p->*function)(args ...);
    }

	template <Return(*function)(Args ...)>
	static void method_stub(Args ... args)
	{
		return (*function)(args ...);
	}
};