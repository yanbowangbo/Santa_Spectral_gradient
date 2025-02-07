function [err,state] = Santa(model,f,opts,state) 

    %% error checking and initialization
    if nargin < 3 
        state = {}; 
    end
    if ~isfield(state,'iter') 
        state.iter = 0; 
    end
    state.iter = state.iter+1;

    
    if isfield(opts,'learningRate')
        lr = opts.learningRate;
    else
        lr = 1;
    end
    if isfield(opts,'RMSpropDecay')
        rmsd = opts.RMSpropDecay;
    else
        rmsd = 0.999;
    end

    if ~isfield(opts, 'decay_grad')
		opts.decay_grad = 0.1;
    end
    
    if ~isfield(opts, 'anne_rate')
        opts.anne_rate = 0.5;
    end
    
    if isfield(opts,'epsilon')
        eps = opts.epsilon;
    else
        eps = 1e-1;
    end
    

    if ~isfield(opts,'reportL2Penalty')
        opts.reportL2Penalty=false;
    end

    params = model.getParameters();
    [err, grad] = f();

    
    if isfield(opts,'weightDecay') && opts.weightDecay > 0
        grad = grad + opts.weightDecay*params;
        if opts.reportL2Penalty 
            err = err + 0.5*opts.weightDecay*dot(params(:),params(:)); 
        end
    end
    
    if isfield(opts,'learningRateOffset') && opts.learningRateOffset >0
        lr=opts.learningRate*((state.iter+opts.learningRateOffset)^-opts.learningRateDecay);

    elseif isfield(opts,'learningRateDecay') && opts.learningRateDecay > 0
        lr= opts.learningRate*(state.iter^-opts.learningRateDecay);
    end
    
    if ~isfield(state,'history')
        state.history = 0+grad.^2; 
    end

    if ~isfield(state,'u')
		state.u = randn(size(grad)) * sqrt(lr);
    end
    
    if ~isfield(opts,'D')
		opts.D = 1000 * sqrt(lr);
    end
    
    if ~isfield(state,'alpha')
        state.alpha = opts.D * ones(size(grad));
    end
    
	if ~isfield(state,'grad')
		state.grad = grad;
	end
	%%% we consider a smooth version of the gradient
	grad = opts.decay_grad * state.grad + (1 - opts.decay_grad) * grad;
	state.grad = grad;

    %% algorithm
    state.history = rmsd*state.history + (1-rmsd)*grad.^2;
    if state.iter < opts.burnin
		pcder=(1e-4 + sqrt(state.history)).^(0.5);
	else
		pcder=(eps + sqrt(state.history)).^(0.5);
    end
    
    factor = state.iter^opts.anne_rate;
	params = params + state.u ./ pcder / 2;
    if state.iter < opts.burnin
        state.alpha = state.alpha + (state.u.^2 - lr / factor) / 2;
    end

    %%% The derivative of the preconditioner for the
    %%% exploration stage is omitted for simplicity, as the influence is 
    %%% minor according to our emperical study. 
	state.u = exp(-state.alpha/2) .* state.u - opts.N * grad * lr ./ pcder / 2;
    
    if state.iter < opts.burnin
		%%% G2 is set to be constant (100) here
		state.u = state.u + sqrt(2 * lr^1.5 * 100 / factor) .* randn(size(grad));
    end

    state.u = exp(-state.alpha/2) .* state.u - opts.N * grad * lr ./ pcder / 2;

	if state.iter < opts.burnin
        state.alpha = state.alpha + (state.u.^2 - lr / factor) / 2;
	end
	params = params + state.u ./ pcder / 2;
    
    model.setParameters(params);
end
