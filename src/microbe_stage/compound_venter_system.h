#pragma once
#include "engine/component_types.h"
#include "engine/typedefs.h"

#include <Entities/Component.h>
#include <Entities/System.h>
//#include <Entities/Components.h>
#include "process_system.h"
#include <unordered_map>
#include <vector>

namespace Leviathan {
class GameWorld;
}

namespace thrive {

class CellStageWorld;
class CompoundVenterComponent : public Leviathan::Component {
public:
    CompoundVenterComponent();

    double storageSpace;
    double storageSpaceOccupied;

    REFERENCE_HANDLE_UNCOUNTED_TYPE(CompoundVenterComponent);

    static constexpr auto TYPE =
        componentTypeConvert(THRIVE_COMPONENT::COMPOUND_VENTER);
};

class CompoundVenterSystem
    : public Leviathan::System<
          std::tuple<CompoundBagComponent&, CompoundVenterComponent&>> {
public:
    /**
     * @brief Updates the system
     */
    void
        Run(GameWorld& world);

    void
        CreateNodes(
            const std::vector<std::tuple<CompoundBagComponent*, ObjectID>>&
                firstdata,
            const std::vector<std::tuple<CompoundVenterComponent*, ObjectID>>&
                seconddata,
            const ComponentHolder<CompoundBagComponent>& firstholder,
            const ComponentHolder<CompoundVenterComponent>& secondholder)
    {
        TupleCachedComponentCollectionHelper(
            CachedComponents, firstdata, seconddata, firstholder, secondholder);
    }

    void
        DestroyNodes(
            const std::vector<std::tuple<CompoundBagComponent*, ObjectID>>&
                firstdata,
            const std::vector<std::tuple<CompoundVenterComponent*, ObjectID>>&
                seconddata)
    {
        CachedComponents.RemoveBasedOnKeyTupleList(firstdata);
        CachedComponents.RemoveBasedOnKeyTupleList(seconddata);
    }

protected:
private:
    int curBiomeId = 0;
    static constexpr double TIME_SCALING_FACTOR = 1000;
};
} // namespace thrive