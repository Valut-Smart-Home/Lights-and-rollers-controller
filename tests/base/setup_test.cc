#include <inttypes.h>
#include <gtest/gtest.h>

#include "../../src/base/setup.h"
#include "../../src/base/module.h"

class SetupExposed : public lights_and_rollers::base::Setup {
    public:
        const std::size_t get_count() { return N; }
        std::size_t get_counter() { return moduleCounter; }
        lights_and_rollers::base::Module** mod{modules};
};

class ModuleFake: public lights_and_rollers::base::Module {
    public:
        ModuleFake(): lights_and_rollers::base::Module(lights_and_rollers::base::Stage::kHardwareInteraction)
        { }
        
        bool isInited{false};
        bool isExecuted{false};
        void Init() override { isInited = true; }
        void Execute() override { isExecuted = true; }
};

TEST(BaseSetup, CreateObjects) {
    SetupExposed setup{};
    auto n = setup.get_count();

    setup.CreateObjects();

    ASSERT_EQ(n, setup.get_counter());

    auto stage = setup.mod[0]->stage;
    for (size_t i = 1; i < n; i++)
    {
        auto new_stage = setup.mod[i]->stage;
        EXPECT_LE(stage, new_stage) << "Stage error in " << i << " module";
        stage = new_stage;
    }
}

TEST(BaseSetup, ReadConfiguration) {
    FAIL() << "Not implemented";
}

TEST(BaseSetup, InitModules) {
    SetupExposed setup{};
    auto n = setup.get_count();

    for (size_t i = 0; i < n; i++)
    {
        setup.mod[i] = new ModuleFake{};
    }
    
    setup.InitModules();

    for (size_t i = 0; i < n; i++)
    {
        auto mod = (ModuleFake*)setup.mod[i];
        EXPECT_TRUE(mod->isInited);
    }
}

TEST(BaseSetup, SetupPowerOut) {
    FAIL() << "Not implemented";
}

TEST(BaseSetup, ExecuteModules) {
    SetupExposed setup{};
    auto n = setup.get_count();

    for (size_t i = 0; i < n; i++)
    {
        setup.mod[i] = new ModuleFake{};
    }
    
    setup.ExecuteModules();

    for (size_t i = 0; i < n; i++)
    {
        auto mod = (ModuleFake*)setup.mod[i];
        EXPECT_TRUE(mod->isExecuted);
    }
}
