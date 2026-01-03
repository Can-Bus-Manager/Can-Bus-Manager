#include "tab_factory.hpp"
#include "core/macro/console_logging.hpp"

namespace AppRoot {

std::unique_ptr<Core::ITabComponent> TabFactory::createByTypeIndex(
    const std::type_index index) const {
    if (const auto it = m_creators.find(index); it != m_creators.end()) {
        return it->second.creator();
    }

    // Log error if type is unknown (using type name for debugging)
    LOG_ERR(AppRoot, "TabFactory: No creator registered for type: {}", index.name());
    return nullptr;
}

bool TabFactory::isRegistered(const std::type_index index) const {
    return m_creators.find(index) != m_creators.end();
}

auto TabFactory::canRestart(const std::type_index index) -> bool {
    if (const auto it = m_creators.find(index); it != m_creators.end()) {
        if (it->second.remainingRestarts > 0) {
            it->second.remainingRestarts--;
            return true;
        }
    }
    return false;
}

} // namespace AppRoot

