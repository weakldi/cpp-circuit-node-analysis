#ifndef ID
#define ID


template<typename T> struct give_id;
template<typename T>
struct id_{
    id_() : m_value(next_id++) {}
    id_(const id_<T>& id) : m_value(id.m_value) {}
    id_(const T& t) : id_(dynamic_cast<const give_id<T>&>(t).m_id) {}

    struct hash{
        int operator () (const id_<T> &p) const {
           auto h =  std::hash<int>{}(p.m_value);
           return h;
        }
    };

    inline bool operator< (const id_<T>& rhs){ return this->m_value < rhs.m_value; }
    inline bool operator> (const id_<T>& rhs){ return rhs < *this; }
    inline bool operator<=(const id_<T>& rhs){ return !(*this > rhs); }
    inline bool operator>=(const id_<T>& rhs){ return !(*this < rhs); }
    private:
        friend bool operator==(const id_<T>& lhs, const id_<T>& rhs){ return lhs.m_value == rhs.m_value; };
        int m_value;
        static int next_id;
};



template<typename T>
struct give_id
{
    public:
        give_id() : m_id() {}
        id_<T> id() const {return m_id;}
    private:
        friend struct id_<T>;
        id_<T> m_id;
        
};
template<typename T>
inline bool operator==(const id_<T>& lhs, const id_<T>& rhs){ return lhs.m_value == rhs.m_value; }
template<typename T>
inline bool operator==(const give_id<T>& lhs, const give_id<T>& rhs){ return lhs.id() == rhs.id(); }
template<typename T>
inline bool operator!=(const id_<T>& lhs, const id_<T>& rhs){ return lhs.m_value != rhs.m_value; }


template<typename T> 
int id_<T>::next_id = 1;

#endif /* HANDEL */
