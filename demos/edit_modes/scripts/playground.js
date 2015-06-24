solver = new c.SimplexSolver();
var min = new c.Variable({
  value: 10
});
var max = new c.Variable({
  value: 15
});


solver.addStay(min);
solver.addStay(max,c.Strength.medium);

/*
solver.addConstraint(new c.StayConstraint(min));
solver.addConstraint(new c.StayConstraint(max));
*/

var expr = c.Expression.fromVariable(min,solver).plus(new c.Expression(20));
var constr = new c.Equation(max, expr);

//var constr = new c.Inequality(min, c.LEQ, max, c.Strength.required);
solver.addConstraint(constr);

console.log("min : "+min.value);
console.log("max : "+max.value);

solver.addEditVar(min)
        .beginEdit();

solver.suggestValue(min, 40);
solver.resolve();

console.log("min : "+min.value);
console.log("max : "+max.value);