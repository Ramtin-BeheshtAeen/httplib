#include <iostream>
#include <memory>

namespace httplib {

namespace detail {



  
// A multimap that keeps its entries in the order they were inserted.
template <typename Mapped, typename KeyEqual>
class insertation_ordered_multimap {
public:
  using size_type = std::size_t;
  using value_type = std::pair<std::string, Mapped>;
  iterator insert(value_type &&val) {
    entries_.push_back(std::move(val));
    return make_itr(entries_.size() - 1 , npos());
  }

  // cursor over the entries:
  /*
    iterator_t is an cursor over the entries;
    - where the data is (data_)
    - which entry it's on (idx_)
    - how many entries exist (size_)
    - whether it's walking every entry or only those with one key (key_idx_)

    Everything else in the class is functions that read the current entry or move the cursor.

    We'll use this example data throughout:
    entries_:  [0] {"Host","a.com"}  [1] {"Set-Cookie","x=1"}  [2] {"Accept","*"}  [3] {"Set-Cookie","y=2"}
  */
  template <typename V> class iterator_t {
  public:
    
  private:
    V *data_;
    size_type idx_;
    size_type size_;
    size_type key_idx_;
  };

  
  
private:
  std::vector<value_type> entries_;
  
};
}
  
  struct Response;

  
  
using Headers =
    detail::insertion_ordered_multimap<std::string,
                                       detail::case_ignore::equal_to>;


class Result {
public:
  Result() = default;
  Result(std::unique_ptr<Response> &&res, Error err,
         Headers &&request_headers = Headers{})
      : res_(std::move(res)), err_(err),
    request_headers_(std::move(request_headers)) {}
};


class Server {
public:
  void say_hello() {};
};


class Client {
 public:
  // explicint unable the compiler to make it befor it is actually asked:
   explicit Client(const std::string &host, int port);
   Result Get(const std::string &path);
};



struct Response {
  std::string version;
  int status = -1;
  std::string reason;
  //Headers headers;
  //Headers trailers;
  std::string body;
  std::string location; // Redirect location

  
};
 
}
