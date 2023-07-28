# part
A programming problem
--Story--
The ship arrived back at the harbor (mostly) in one piece. You have already walked through the
ship and have noted the problems with the ship. You don’t have the time (or parts) to repair the
ship, so you will rely on a third party group to make the ship seaworthy again.
You fear that the repair crew will overcharge you. For this reason you want to write a program
that will determine an estimate as to how much money the repair will cost. You are certain that
they won’t look for problems. The repair crew maintains a list of broken components that need
to be fixed. The list begins empty, because they don’t look for the problems directly. The repair
crew will try to turn the ship on, and while some component is still broken, the repair crew will
look for the most obvious component that is broken and add that component to the end of the
list of broken components to fix.
Sometimes when a component is fixed it will reveal additional components that need to be fixed.
Those revealed components will be added to the end of the list of components to fix assuming
that they are still broken in the order they are revealed.
To fix a component a part will be required. If the part is available the repair crew will expend the
part and the component will be fixed. If the required part is not available, then the repair crew
will place an order for the part from some distribution center, but to charge you extra they will
order an additional part from the distribution center claiming that it can save you money in the
long run. For each part type you know the additional part type that will be ordered and the cost
of order said parts. Since it takes a little bit of time to get the part once it has been ordered, the
crew will place the component at the end of the list of components to fix. The good news is that
by the time the next component in the list of components to fix is examined the 2 parts ordered
will have arrived.
You want to know the sum of all the costs of all the parts ordered based on the repair crews
repair procedure.

--Problem--
Given a list of parts pairs and their cost, the components that are broken in order of their
obviousness, and the components that are revealed when a component is fixed. Determine the
amount of money you will have to pay to repair the ship.

--Input--
Input will begin with a line containing 1 integer, P (1 ≤ P ≤ 100,000), representing the number of
parts that can be used to repair the ship. The following P lines will each contain 2 integers, c
and e, (1 ≤ c ≤ 100,000; 1 ≤ e ≤ P) representing the cost of ordering the part corresponding and
the extra part that will be received at “no extra” cost.
The next line of input will contain a single integer, C (1 ≤ C ≤ 500,000), representing the number
of components that need to be repaired. The most obvious broken component will always be
the one with the lowest index. Following this will be C lines each beginning with 2 integers, p
and n (1 ≤ p ≤ P; 0 ≤ n ≤ C - 1), representing the part needed to repair the corresponding
component and the number of broken components revealed upon repairing the component. On
this same line will follow n integers all in the range of [1, C] representing the components that
are revealed when the corresponding component is repaired.
It guaranteed that the sum of all n’s is less than 5,000,000


--Output--
Output should contain a single line with a single integer representing the price the repair crew
will charge in costs for ordering all the parts.

