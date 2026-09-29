# AI Usage Report

## Tools used
- ChatGPT - used for scaffolding, brainstorming test cases, and
  generating the initial plot.py matplotlib boilerplate.
- All algorithm logic, complexity analysis, and final code review
  were done by hand.

## How AI assisted
- Helped: generating boilerplate (CMakeLists, CI YAML), suggesting the
  paired-scan MINMAX structure, and drafting the plotting script.
- Did not help (had to be fixed manually): the first AI-generated
  median-of-medians implementation had an off-by-one error in the
  recursion; caught by the correctness tests.
- AI also initially miscounted comparisons in quicksort partitioning.

## Assessment
Using AI sped up boilerplate-heavy parts by roughly 2x. For the
algorithmic core - especially the median-of-medians constant-factor
analysis - AI output required careful verification.
Net effect: positive for productivity, neutral for learning if used
uncritically.