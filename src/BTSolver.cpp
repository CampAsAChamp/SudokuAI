#include "BTSolver.hpp"

using namespace std;

// =====================================================================
// Constructors
// =====================================================================

BTSolver::BTSolver(SudokuBoard input, Trail *_trail, string val_sh, string var_sh, string cc)
	: sudokuGrid(input.get_p(), input.get_q(), input.get_board()), network(input)
{
	valHeuristics = val_sh;
	varHeuristics = var_sh;
	cChecks = cc;

	trail = _trail;
}

// =====================================================================
// Consistency Checks
// =====================================================================

// Basic consistency check, no propagation done
bool BTSolver::assignmentsCheck(void)
{
	for (Constraint c : network.getConstraints())
		if (!c.isConsistent())
			return false;

	return true;
}

/**
 * Part 1 TODO: Implement the Forward Checking Heuristic
 *
 * This function will do both Constraint Propagation and check
 * the consistency of the network
 *
 * (1) If a variable is assigned then eliminate that value from
 *     the square's neighbors.
 *
 * Note: remember to trail.push variables before you change their domain
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::forwardChecking(void)
{
	int numChanges = 0;
	do
	{
		numChanges++;

		// Get all of the constraints that were changed from last move
		for (Constraint *c : network.getModifiedConstraints())
		{
			for (Variable *v : c->vars)
			{
				// Only forward check the variables(box) that have been assigned and we can eliminate from its neighbors
				if (v->isAssigned())
				{
					for (Variable *neighbor : network.getNeighborsOfVariable(v))
					{
						// Check the domain of the neighbors and if our recently assigned variable is in there
						if (neighbor->getDomain().contains(v->getAssignment()))
						{
							trail->push(neighbor);								 // Add the previous state to the trail so we can backtrack
							neighbor->removeValueFromDomain(v->getAssignment()); // Remove the assigned variable
							numChanges = 0;										 // Reset the counter so we have to forward check again
						}
					}
				}
			}
		}
	} while (numChanges == 0);

	// Debugging code for checking the domain of all the variables
	// for (Variable *v : network.getVariables())
	// {
	// 	cout << v->toString() << endl;
	// }

	// Go through the board to make sure it's consistent and there aren't any empty squares
	for (Variable *v : network.getVariables())
	{
		if (v->getDomain().isEmpty())
		{
			return false;
		}
	}
	return true;
}

/**
 * Part 2 TODO: Implement both of Norvig's Heuristics
 *
 * This function will do both Constraint Propagation and check
 * the consistency of the network
 *
 * (1) If a variable is assigned then eliminate that value from
 *     the square's neighbors.
 *
 * (2) If a constraint has only one possible place for a value
 *     then put the value there.
 *
 * Note: remember to trail.push variables before you change their domain
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::norvigCheck(void)
{
	int numChanges = 0;
	do
	{
		numChanges++;

		// Get all of the constraints that were changed from last move
		for (Constraint *c : network.getModifiedConstraints())
		{
			for (Variable *v : c->vars)
			{
				// Only forward check the variables(box) that have been assigned and we can eliminate from its neighbors
				if (v->isAssigned())
				{
					for (Variable *neighbor : network.getNeighborsOfVariable(v))
					{
						// Check the domain of the neighbors and if our recently assigned variable is in there
						if (neighbor->getDomain().contains(v->getAssignment()))
						{
							trail->push(neighbor);								 // Add the previous state to the trail so we can backtrack
							neighbor->removeValueFromDomain(v->getAssignment()); // Remove the assigned variable
							numChanges = 0;										 // Reset the counter so we have to forward check again
						}
					}
				}
				else
				{
					// Unassigned Var Domain
					for (int value : v->getDomain())
					{
						bool assignable = true;

						// Iterate through neighbor's domain
						for (Variable *neighbor : network.getNeighborsOfVariable(v))
						{
							if (neighbor->getDomain().contains(value))
							{
								assignable = false;
								break;
							}
						}

						// If a unit has only one possible place for a value, then put the value there.
						if (assignable)
						{
							trail->push(v);
							v->assignValue(value);
							break;
						}
					}
				}
			}
		}
	} while (numChanges == 0);

	// Go through the board to make sure it's consistent and there aren't any empty squares
	for (Variable *v : network.getVariables())
	{
		if (v->getDomain().isEmpty())
		{
			return false;
		}
	}

	return true;
}

/**
 * Optional TODO: Implement your own advanced Constraint Propagation
 *
 * Completing the three tourn heuristic will automatically enter
 * your program into a tournament.
 */
bool BTSolver::getTournCC(void)
{
	return false;
}

// =====================================================================
// Variable Selectors
// =====================================================================

// Basic variable selector, returns first unassigned variable
Variable *BTSolver::getfirstUnassignedVariable(void)
{
	for (Variable *v : network.getVariables())
		if (!(v->isAssigned()))
			return v;

	// Everything is assigned
	return nullptr;
}

/**
 * Part 1 TODO: Implement the Minimum Remaining Value Heuristic
 *
 * Return: The unassigned variable with the smallest domain
 */
Variable *BTSolver::getMRV(void)
{
	Variable *mrv = getfirstUnassignedVariable();

	// If there are no unassigned variables, then no work should be done.
	if (mrv == nullptr)
		return nullptr;
	else
	{
		// Current minimum domain count in MRV.
		int minSize = mrv->size();

		for (Variable *var : network.getVariables())
		{
			if (var->isAssigned() == false)
			{
				if (var->size() == minSize || var->size() < minSize)
				{
					// Found new minimum
					minSize = var->size();

					// Setting the new mrv to be the minimum var
					mrv = var;
				}
			}
		}
	}

	return mrv;
}

/**
 * Part 2 TODO: Implement the Minimum Remaining Value Heuristic
 *                with Degree Heuristic as a Tie Breaker
 *
 * Return: The unassigned variable with the smallest domain and involved
 *             in the most constraints
 */
Variable *BTSolver::MRVwithTieBreaker(void)
{
	Variable *mrv = getfirstUnassignedVariable();

	// If there are no unassigned variables, then no work should be done.
	if (mrv == nullptr)
		return nullptr;
	else
	{
		double max_constraints = network.getConstraintsContainingVariable(mrv).size();

		// Current minimum domain count in MRV.
		int minSize = mrv->size();

		for (Variable *var : network.getVariables())
		{
			if (var->isAssigned() == false)
			{
				if (var->size() == minSize || var->size() < minSize)
				{
					// Found new minimum
					minSize = var->size();

					// Setting the new mrv to be the minimum var
					mrv = var;
					max_constraints = network.getConstraintsContainingVariable(mrv).size();
				}
			}
		}
	}

	return mrv;
}

/**
 * Optional TODO: Implement your own advanced Variable Heuristic
 *
 * Completing the three tourn heuristic will automatically enter
 * your program into a tournament.
 */
Variable *BTSolver::getTournVar(void)
{
	return nullptr;
}

// =====================================================================
// Value Selectors
// =====================================================================

// Default Value Ordering
vector<int> BTSolver::getValuesInOrder(Variable *v)
{
	vector<int> values = v->getDomain().getValues();
	sort(values.begin(), values.end());
	return values;
}

/**
 * Part 1 TODO: Implement the Least Constraining Value Heuristic
 *
 * The Least constraining value is the one that will knock the least
 * values out of it's neighbors domain.
 *
 * Return: A list of v's domain sorted by the LCV heuristic
 *         The LCV is first and the MCV is last
 */

// Comparator for our pair to sort based on the second item in the pair
bool sortBySecondItem(const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.second < b.second);
}

vector<int> BTSolver::getValuesLCVOrder(Variable *v)
{
	vector<int> valuesInOrder = getValuesInOrder(v);
	vector<pair<int, int>> counts(valuesInOrder.size());
	vector<int> sortedValues(valuesInOrder.size());

	// Initialize the vector of pairs so it will become <value, count> i.e <1,4> and <2, 11>
	for (int i = 0; i < valuesInOrder.size(); i++)
	{
		counts[i].first = valuesInOrder[i];
		counts[i].second = 0;
	}

	// For every value in our board find every variable if its touching and increment its count
	for (int i = 0; i < valuesInOrder.size(); i++)
	{
		for (Variable *v1 : network.getNeighborsOfVariable(v))
		{
			if (v1->getDomain().contains(valuesInOrder[i]))
			{
				counts[i].second++;
			}
		}
	}

	sort(counts.begin(), counts.end(), sortBySecondItem);

	// Debugging code to print the vector
	// for(int i = 0; i < counts.size(); i++)
	// {
	//     cout << counts[i].first << ": " << counts[i].second << "| ";
	// }
	// cout << endl;

	// Since we need to return a single int array of the numbers put them in the return vector and disregard the counts for the return vector
	for (int i = 0; i < counts.size(); i++)
	{
		sortedValues[i] = counts[i].first;
	}

	return sortedValues;
}

/**
 * Optional TODO: Implement your own advanced Value Heuristic
 *
 * Completing the three tourn heuristic will automatically enter
 * your program into a tournament.
 */
vector<int> BTSolver::getTournVal(Variable *v)
{
	return vector<int>();
}

// =====================================================================
// Engine Functions
// =====================================================================

void BTSolver::solve(void)
{
	if (hasSolution)
		return;

	// Variable Selection
	Variable *v = selectNextVariable();

	if (v == nullptr)
	{
		for (Variable *var : network.getVariables())
		{
			// If all variables haven't been assigned
			if (!(var->isAssigned()))
			{
				cout << "Error" << endl;
				return;
			}
		}

		// Success
		hasSolution = true;
		return;
	}

	// Attempt to assign a value
	for (int i : getNextValues(v))
	{
		// Store place in trail and push variable's state on trail
		trail->placeTrailMarker();
		trail->push(v);

		// Assign the value
		v->assignValue(i);

		// Propagate constraints, check consistency, recurse
		if (checkConsistency())
			solve();

		// If this assignment succeeded, return
		if (hasSolution)
			return;

		// Otherwise backtrack
		trail->undo();
	}
}

bool BTSolver::checkConsistency(void)
{
	if (cChecks == "forwardChecking")
		return forwardChecking();

	if (cChecks == "norvigCheck")
		return norvigCheck();

	if (cChecks == "tournCC")
		return getTournCC();

	return assignmentsCheck();
}

Variable *BTSolver::selectNextVariable(void)
{
	if (varHeuristics == "MinimumRemainingValue")
		return getMRV();

	if (varHeuristics == "MRVwithTieBreaker")
		return MRVwithTieBreaker();

	if (varHeuristics == "tournVar")
		return getTournVar();

	return getfirstUnassignedVariable();
}

vector<int> BTSolver::getNextValues(Variable *v)
{
	if (valHeuristics == "LeastConstrainingValue")
		return getValuesLCVOrder(v);

	if (valHeuristics == "tournVal")
		return getTournVal(v);

	return getValuesInOrder(v);
}

bool BTSolver::haveSolution(void)
{
	return hasSolution;
}

SudokuBoard BTSolver::getSolution(void)
{
	return network.toSudokuBoard(sudokuGrid.get_p(), sudokuGrid.get_q());
}

ConstraintNetwork BTSolver::getNetwork(void)
{
	return network;
}
