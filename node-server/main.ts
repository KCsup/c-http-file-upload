Deno.serve(async (request: Request) => {
  const reqBody = await request.formData();
  for (const pair of reqBody.entries()) {
    const field = pair[0], val = pair[1];
    if (val instanceof File) {
      console.log("FILE =>", field, val);
    } else {
      console.log("FIELD =>", field, val);
    }
  }
  return new Response(null, { status: 201 });
}, { port: 8000 });
