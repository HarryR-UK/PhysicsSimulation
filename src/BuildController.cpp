#include "../include/BuildController.h"

using namespace Builder;

BuildController::BuildController( Simulation& sim )
    : m_sim(sim)
{
}

void BuildController::buildModeControls()
{

}

void BuildController::nonBuildModeControls()
{

}

void BuildController::getInput()
{

}

const bool BuildController::getIsBuildMode() const
{
    return m_isBuildActive;
}

const void BuildController::setIsBuildMode(bool& value)
{
    m_isBuildActive = value;
}
