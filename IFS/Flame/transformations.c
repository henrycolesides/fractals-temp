// Affine transformations
double[2] scale(double p[2], double * args)
{
  double p2[2] = {p[0] * args[0], p[1] * args[1]};
  return p2;
}

double[2] translate(double p[2], double * args)
{
  double p2[2] = {p[0] + args[0], p[1] + args[1]};
  return p2;
}

double[2] rotate(double p[2], double * args)
{
  double p2[2];
  double temp;

  temp  = p[0]*cos(args[0]) - p[1]*sin(args[0]);
  p2[1] = p[0]*sin(args[0]) + p[1]*cos(args[0]);
  p2[0] = temp;

  return p2;
}


// Non-linears
double[2] identity(double p[2], double * args)
{
    return p;
}
