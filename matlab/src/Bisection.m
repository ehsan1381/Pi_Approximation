function [Steps] = Bisection(f, Start, End, TOL)

    N_0 = ceil( ( log( End - Start ) - log( TOL ) ) / log( 2 ) )
    if 2 * eps >= TOL
        disp(['The bisection method will not be able to produce results accurate to ' num2str(TOL)]);
        return;
    end

    tic;
    Steps = zeros([N_0 6]);
    index = 1;
    FA = f(Start);
    fprintf('index\tStart\tEnd\tFA\tmiddle point\tFP\n');
    while index <= N_0

        middle_point = (End-Start) / 2;
        Approximation = Start + middle_point;

        FP = f(Approximation);
        Steps(index, :) = [index;Start;End;FA;Approximation;FP];
        if FA == 0 || f(End) == 0
            if FA == 0
                Approximation = Start;

            else
                Approximation = End;
            end
            disp(Approximation);
            toc;
            return ;
        end

        if (FP == 0) || abs(middle_point) < TOL
            disp(Approximation);
            toc;
            return ;
        end
        index = index + 1;

        if sign(FA) * sign(FP) > 0
            Start = Approximation;
            FA = FP;
        else
            End=Approximation;
        end


    end

    disp(["Failure after ", num2str(N_0)]);
    toc;
end
