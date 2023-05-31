#include <thread>
#include <sofa/helper/BackTrace.h>
#include <sofa/helper/system/PluginManager.h>
#include <sofa/simulation/Node.h>
#include <sofa/simulation/graph/DAGSimulation.h>
#include <sofa/simulation/graph/init.h>
#include <sofa/simulation/graph/SimpleApi.h>

int main()
{
    sofa::helper::BackTrace::autodump();

    sofa::simulation::graph::init();
    sofa::simulation::setSimulation(new sofa::simulation::graph::DAGSimulation());

    sofa::helper::system::PluginManager::getInstance().loadPlugin("Sofa.Component");

    sofa::simulation::Node::SPtr root1 = sofa::simpleapi::createNode("root1");
    sofa::simulation::Node::SPtr root2 = sofa::simpleapi::createNode("root2");

    for (auto& r : {root1, root2})
    {
        sofa::simpleapi::createObject(r, "DefaultAnimationLoop");
        sofa::simpleapi::createObject(r, "EulerImplicitSolver");
        sofa::simpleapi::createObject(r, "EigenSimplicialLDLT", {{"template", "CompressedRowSparseMatrixMat3x3"}, {"ordering", "Natural"}});
        sofa::simpleapi::createObject(r, "MechanicalObject", {{"name", "state"}});
        sofa::simpleapi::createObject(r, "RegularGridTopology", {{"nx","8"}, {"ny","8"}, {"nz","40"}, {"xmin","-9"}, {"xmax","-6"}, {"ymin","0"}, {"ymax","3"}, {"zmin","0"}, {"zmax","19"}});
        sofa::simpleapi::createObject(r, "UniformMass", {{"totalMass", "320"}});
        sofa::simpleapi::createObject(r, "BoxROI", {{"name", "box"}, {"box", "-10 -1 -0.0001  -5 4 0.0001"}});
        sofa::simpleapi::createObject(r, "FixedConstraint", {{"indices","@box.indices"}});
        sofa::simpleapi::createObject(r, "HexahedronFEMForceField", {{"youngModulus","4000"}, {"poissonRatio","0.3"}, {"method","large"}});

        sofa::simulation::getSimulation()->init(r.get());
    }

    const auto simulate = [](sofa::simulation::Node::SPtr rootNode)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (std::size_t i = 0; i < 100; ++i)
        {
            sofa::simulation::getSimulation()->animate(rootNode.get(), 0.1_sreal);
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << rootNode->getName() << " Execution time: " << duration << " milliseconds" << std::endl;
    };

    const auto start = std::chrono::high_resolution_clock::now();

    std::thread threadSimulation1(simulate, root1);
    std::thread threadSimulation2(simulate, root2);

    threadSimulation1.join();
    threadSimulation2.join();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Total execution time: " << duration << " milliseconds" << std::endl;


    sofa::simulation::graph::cleanup();
    return 0;
}
