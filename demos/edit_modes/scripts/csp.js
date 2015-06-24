"use strict";


function TimeNode(solver, date)
{
	// structure -------------
	this.events = [];

	// variables solver -------------
	this.date = new c.Variable({ value: date });

	// contraintes solver ---------------
	this.constraints = [];

	// graphics ---------------
	this.yTop = new c.Variable({ value: 0 });
	this.yBot = new c.Variable({ value: 100 });

	this.applyconstraints = function(solver, strategy)
	{
		strategy.timeNode.applyconstraints.call(this,solver);

		this.events.forEach(function(event)
		{
			event.applyconstraints(solver, strategy);
		});

		this.strategy = strategy;
	};

	this.draw = function(solver, paper)
	{
		drawTimeNode.call(this,paper);

		this.events.forEach(function(event)
		{
			event.draw(solver, paper);
		});
	};

}

function Event(solver, timeNode, yPos)
{
	// structure -------------
	this.timeNode = timeNode;
	this.nextTimeRelations = [];
	this.prevTimeRelations = [];

	this.timeNode.events.push(this);
	// variables solver -------------
	// N/A

	// contraintes solver ---------------
	this.constraints = [];

	// graphics ---------------
	this.y = new c.Variable({ value: yPos });
	this.handle = {};

	this.applyconstraints = function(solver, strategy)
	{

		// strategy related
		strategy.event.applyconstraints.call(this,solver);

		this.nextTimeRelations.forEach(function(timeRelation)
		{
			timeRelation.applyconstraints(solver, strategy);
		});

		// strategy independent constraints
		// graphics related
		var constr;

		// yBot pos of timenode
		constr = new c.Inequality(this.y, c.LEQ, this.timeNode.yBot, c.Strength.required);
		solver.addConstraint(constr);

		// yTop pos of timenode
		constr = new c.Inequality(this.y, c.GEQ, this.timeNode.yTop, c.Strength.required);
		solver.addConstraint(constr);

		this.strategy = strategy;
	};

	this.draw = function(solver, paper)
	{
		this.handle = drawEvent.call(this,paper);

		this.strategy.event.dragBehavior.call(this, solver);

		this.nextTimeRelations.forEach(function(timeRelation)
		{
			timeRelation.draw(solver, paper);
		});
	};

}


function TimeRelation(solver, nom, min, max, antEvent, postEvent)
{
	// structure -------------
	this.antEvent = antEvent;
	this.postEvent = postEvent;

	this.antEvent.nextTimeRelations.push(this);
	this.postEvent.prevTimeRelations.push(this);

	// variables solver -------------
	this.nom = new c.Variable({ value: nom });

	this.min = new c.Variable({ value: min });

	this.max = new c.Variable({ value: min });

	// contraintes solver ---------------
	this.constraints = [];
	
	this.applyconstraints = function(solver, strategy)
	{
		//strategy related
		strategy.timeRelation.applyconstraints.call(this,solver);
		
		//strategy independent constraints
		var constr,expr;

		// min <= max
		constr = new c.Inequality(this.min, c.LEQ, this.max, c.Strength.required);
		solver.addConstraint(constr);

		// min >= 0
		constr = new c.Inequality(this.min, c.GEQ, 0, c.Strength.required);
		solver.addConstraint(constr);

		// min <= nom
		constr = new c.Inequality(this.min, c.LEQ, this.nom, c.Strength.required);
		solver.addConstraint(constr);

		// nom <= max
		constr = new c.Inequality(this.nom, c.LEQ, this.max, c.Strength.required);
		solver.addConstraint(constr);

		/*
		// ant + nom = post
		var antDate = this.antEvent.timeNode.date;
		var postDate = this.postEvent.timeNode.date;
		expr = c.Expression.fromVariable(antDate, solver).plus(this.nom);
		constr = new c.Equation(postDate, expr);
		solver.addConstraint(constr);
		*/
		
		this.strategy = strategy;
	}

	this.isRigid = function()
	{
		if(this.min.value == this.max.value)
		{
			return true;
		}else
		{
			return false;
		}
	};

	this.draw = function(solver, paper)
	{
		drawTimeRelation.call(this,paper);
	};
}


var eventRadius = 4;

function drawEvent(paper)
{
	return paper.circle(this.timeNode.date.value, this.y.value, eventRadius).attr("fill","black");
}

function drawTimeNode(paper)
{
	return paper.path("M"+this.date.value+","+this.yTop.value+"L"+this.date.value+","+this.yBot.value);
}

function drawTimeRelation(paper)
{
	var xAnt = this.antEvent.timeNode.date.value;
	var y = this.antEvent.y.value;
	var xMin = xAnt+this.min.value;
	var xMax = xAnt+this.min.value;

	paper.path("M"+xAnt+","+y+"L"+xMin+","+y);

	paper.path("M"+xMin+","+y+"L"+xMax+","+y).attr("stroke-dasharray","-");

	//TODO: return set?
}

var strategy1 = {
	event : {
		applyconstraints : function(solver){
			solver.addStay(this.y, c.Strength.required);
		},
		dragBehavior : function(solver)
		{
			this.handle.drag(
				function(dx,dy)//onmonve
				{
					solver.suggestValue(this.timeNode.date,this.startDateValue+dx);
					solver.suggestValue(this.y,this.startYValue+dy);
					solver.resolve();
					scenario.reDraw(solver, this.handle.paper);
				},
				function()//onstart
				{
					this.startDateValue = this.timeNode.date.value;
					this.startYValue = this.y.value;

					solver.addEditVar(this.timeNode.date)
						.addEditVar(this.y)
        		.beginEdit();
				},
				function()//onend
				{
					console.log(this.timeNode.date.value);
					solver.endEdit();

					console.log(this.timeNode.date.value);
				}
				,this,this,this
				)
		}
	},
	timeNode : {
		applyconstraints : function(solver){
			var constr;

			solver.addStay(this.date, c.Strength.weak);
		}
	},
	timeRelation : {
		applyconstraints : function(solver)
		{
			var constr;
			//min and max don't change
			solver.addStay(this.min, c.Strength.required);
			solver.addStay(this.max, c.Strength.required);

			//nom can easily change
			solver.addStay(this.nom, c.Strength.medium);
		}
	}
};

function Scenario()
{
	this.timeNodes = [];

	this.reDraw = function(solver, paper)
	{
		paper.clear();

		this.timeNodes.forEach(function(timeNode)
		{
			timeNode.draw(solver, paper);
		});
	};

	this.updateStrategy = function(solver,strategy)
	{
		solver = new c.SimplexSolver();
		this.timeNodes.forEach(function(timeNode)
		{
			timeNode.applyconstraints(solver, strategy);
		});
	};
}

//############# RUN ################
var solver;
var scenario;
var paper;

window.onload = function()
{
	solver = new c.SimplexSolver();
	scenario = new Scenario();
	paper = Raphael("paper", 800, 400);

	//nodes
	var t1 = new TimeNode(solver, 10);
	scenario.timeNodes.push(t1);

	var t2 = new TimeNode(solver, 110);
	scenario.timeNodes.push(t2);

	var t3 = new TimeNode(solver, 210);
	scenario.timeNodes.push(t3);

	var t4 = new TimeNode(solver, 310);
	scenario.timeNodes.push(t4);

	//events
	var e1_1 = new Event(solver, t1, 10);
	var e1_2 = new Event(solver, t1, 50);

	var e2_1 = new Event(solver, t2, 10);
	var e2_2 = new Event(solver, t2, 30);

	var e3_1 = new Event(solver,t3, 10);
	var e3_2 = new Event(solver,t3, 30);
	var e3_3 = new Event(solver,t3, 50);

	var e4_1 = new Event(solver,t4, 10);

	//rels
	var c1 = new TimeRelation(solver, 100, 80, 120, e1_1, e2_1);
	var c2 = new TimeRelation(solver, 200, 180, 220, e1_2, e3_3);
	var c3 = new TimeRelation(solver, 100, 80, 120, e2_2, e3_2);
	var c4 = new TimeRelation(solver, 100, 80, 120, e3_1, e4_1);

	scenario.updateStrategy(solver,strategy1);
	solver.resolve();
	scenario.reDraw(solver,paper);
};

