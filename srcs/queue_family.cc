#include <queue_family.hh>

namespace Application {

bool QueueFamilyIndices::isComplete() {
  return graphicsFamily.has_value() && presentFamily.has_value();
}

}
